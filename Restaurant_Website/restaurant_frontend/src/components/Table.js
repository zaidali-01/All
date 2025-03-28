import { useState } from 'react';
import style from './Signup.module.css';
import { useNavigate } from 'react-router-dom';
import { useCreateTableMutation } from '../rtkquery/Api';


function Table()
{
    const [createTable,{isSuccess}] = useCreateTableMutation();
    const [capacity,setcapacity] = useState();
    const [error,seterror] = useState('');
    const navigate = useNavigate();

    const handletable = async (e) =>
    {
        e.preventDefault();
        if(!capacity)
        {
            seterror('Capacity not entered');
            return;
        }
        if(capacity<=0)
        {
            seterror('Invalid Capacity');
            return;
        }

        try
        {
            const result = await createTable(capacity);
            if(result?.data?.msg==='table created!')
            {
                navigate('/');
            }
            else
            {
                seterror(result?.error?.data?.msg || 'Cannot Add Table')
            }
        }
        catch(err)
        {
            seterror('Cannot Add Table');
        }

    }

    return(
        <>
        <div id={style.main}>
        <div className={style['header-bar']}>
          <h1 className={style['header-bar-h1']}>Fusion Bytes</h1>
        </div>
        <div className={style["form-container"]}>
          <h2 className={style["form-container-h2"]}>Add Table</h2>
          <form onSubmit={handletable}>
            <div className={style['form-group']}>
                <label>Table Capacity:</label>
                <input type="number" min="1" step="1" value={capacity} onChange={(e)=>{setcapacity(e.target.value); seterror('')}}/>
            </div>
            {error && <p style={{color:'red'}}>{error}</p>}
            <button onClick={()=>navigate('/')}>Back</button>
            <button type="submit" style={{marginLeft:"10px"}} onClick={()=>seterror('')}>Add</button>
          </form>
        </div>
      </div>
        </>
    )
}

export default Table;