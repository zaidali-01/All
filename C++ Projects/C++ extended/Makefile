CXX = clang++

LLVM_CONFIG = llvm-config
LLVM_CXXFLAGS = $(shell $(LLVM_CONFIG) --cxxflags)
LLVM_LDFLAGS = $(shell $(LLVM_CONFIG) --ldflags --libs core)

SRC = 22L-7001_LLVM.cpp
OUT = LLVM_IR
IR_FILE = output.ll

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(LLVM_CXXFLAGS) $(SRC) -o $(OUT) $(LLVM_LDFLAGS)

ir: $(OUT)
	./$(OUT) > $(IR_FILE)

run: $(OUT)
	./$(OUT)

clean:
	rm -f $(OUT) $(IR_FILE)
