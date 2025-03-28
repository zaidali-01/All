#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/raw_ostream.h>
#include <vector>
#include <memory>

using namespace llvm;

int main() 
{
    LLVMContext ctx;
    std::unique_ptr<Module> mod = std::make_unique<Module>("LLVM_IR_Generation", ctx);
    IRBuilder<> builder(ctx);

    std::vector<Type*> ints(2, Type::getInt32Ty(ctx));
    FunctionType *modType = FunctionType::get(Type::getInt32Ty(ctx), ints, false);
    Function *modFunc = Function::Create(modType, Function::ExternalLinkage, "mod", mod.get());

    BasicBlock *entry = BasicBlock::Create(ctx, "entry", modFunc);
    builder.SetInsertPoint(entry);

    auto args = modFunc->args();
    Function::arg_iterator argsIter = modFunc->arg_begin();
    Value *x = argsIter++;
    x->setName("x");
    Value *y = argsIter++;
    y->setName("y");

    Value *res = builder.CreateSRem(x, y, "mod_res");
    builder.CreateRet(res);

    FunctionType *mainType = FunctionType::get(Type::getInt32Ty(ctx), false);
    Function *mainFunc = Function::Create(mainType, Function::ExternalLinkage, "main", mod.get());
    BasicBlock *mainBB = BasicBlock::Create(ctx, "entry", mainFunc);
    builder.SetInsertPoint(mainBB);

    FunctionType *printfType = FunctionType::get(Type::getInt32Ty(ctx), PointerType::get(Type::getInt8Ty(ctx), 0), true);
    FunctionCallee printfFunc = mod->getOrInsertFunction("printf", printfType);
    Value *helloStr = builder.CreateGlobalStringPtr("Hello, World!\n", "helloStr");
    builder.CreateCall(printfFunc, {helloStr});

    Value *arg1 = ConstantInt::get(Type::getInt32Ty(ctx), 10);
    Value *arg2 = ConstantInt::get(Type::getInt32Ty(ctx), 3);
    Value *modRes = builder.CreateCall(modFunc, {arg1, arg2}, "mod_res");

    builder.CreateRet(ConstantInt::get(Type::getInt32Ty(ctx), 0));

    verifyModule(*mod, &errs());
    mod->print(outs(), nullptr);

    return 0;
}
