import { useState } from 'react';
import { useGetMenuByCategoryQuery, useMakeOrderMutation } from '../rtkquery/Api';
import style from './Addreservation.module.css';

function Order(props)
{
    const [makeorder,{isSuccess,isLoading}] = useMakeOrderMutation();
    const [name,setname] = useState('');
    const [category,setcategory] = useState('');
    const [quantity,setquantity] = useState('');
    const [error,seterror] = useState('');
    const {data} = useGetMenuByCategoryQuery(category);

    const handleorder = async (e) =>
    {
        e.preventDefault();

        seterror('');
        
        if(!category)
        {
            seterror('Category not selected');
        }

        if(!name)
        {
            seterror('Item not selected');
            return;
        }

        if(!quantity || quantity<1)
        {
            seterror('Invalid Quantity');
            return;
        }

        seterror('');
    try{
        const result = await makeorder({rid:props?.reserve?._id,name,category,quantity});
        if (result?.data && result.data?.msg === 'order made') 
        {
            props.fun(false);
        }
        else
        {
            seterror(result?.error?.data?.msg || 'Cannot order at the moment!');
        }
    }
    catch(err)
    {
        seterror('Cannot order at the moment');
    }

    setcategory('');
    setname('');
    setquantity('');

    }

    return(
                            <div className={style['order-container']}>
                                <h2>Order Food</h2>
                                <form id="order-form" onSubmit={handleorder}>
                                    <div className={style['form-group']}>
                                        <label htmlFor="category">Select Category:</label>
                                        <select id="category" name="category" value={category} onChange={(e)=>{setcategory(e.target.value); seterror('')}}>
                                            <option>--Select Category--</option>
                                            <option value="Fast Food">Fast Food</option>
                                            <option value="Desi Food">Desi Food</option>
                                            <option value="BBQ">BBQ</option>
                                            <option value="Dessert">Dessert</option>
                                            <option value="Drinks">Drinks</option>
                                        </select>
                                    </div>
                                    <div className={style['form-group']}>
                                        <label htmlFor="item">Select Item:</label>
                                        <select id="item" name="item" value={name} onChange={(e)=>{setname(e.target.value); seterror('')}}>
                                            {!category ?
                                            <option>--First Select Category--</option> :
                                            <>
                                            <option>--Select Item--</option>
                                            {data?.items?.map((item)=><option value={item?.name}>{item?.name}</option>)}
                                            </>}
                                        </select>
                                    </div>
                                    <div className={style['form-group']}>
                                        <label htmlFor="quantity">Quantity:</label>
                                        <input type="number" min="1" step="1" id="quantity" name="quantity" value={quantity} onChange={(e)=>{setquantity(e.target.value); seterror('')}} />
                                    </div>
                                    {error && <p style={{color:'red'}}>{error}</p>}
                                    <button className={style['done-btn']} onClick={() => props.fun(false)}>Cancel</button>
                                <button type='submit' className={style['done-btn']} >Done</button>
                                </form>
                            </div>);
}

export default Order;