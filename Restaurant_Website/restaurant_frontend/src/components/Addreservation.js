import style from './Addreservation.module.css';
import { useState, useEffect } from 'react';
import { useNavigate } from 'react-router-dom';
import { useReserveTableMutation, useGetUserQuery, useGetAllReservationsQuery } from '../rtkquery/Api';

function Useremail(props)
{
    const {data,isSuccess} = useGetUserQuery(props?.email);
    useEffect(()=>{if(isSuccess){ props?.fun(data?.uid);}},[isSuccess]);
}

function Addreservation() 
{
    const [reserveTable, {isLoading,isSuccess}] = useReserveTableMutation();
    const [error,seterror] = useState('');
    const [email,setemail] = useState('');
    const [time,settime] = useState('');
    const [date,setdate] = useState('');
    const [members,setmembers] = useState('');
    const [u,setu] = useState(null);
    const [r,setr] = useState(false);
    const [a,seta] = useState(false);
    const navigate = useNavigate();
    
    useEffect(()=>{(isSuccess && r) && navigate('/viewreservation')},[isSuccess,r]);
    useEffect(() => {if(u){handlereserve();}}, [u]);

    const validateEmail = (email) =>
    {
      const emailPattern = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
      const b = emailPattern.test(email);
      if(b)
      {
        seta(true);
      }
      else
      {
        seterror('Invalid email format');
      }
      return b;
    }

    const handlereserve = async (e) =>
    {
    
            if (error==='Invalid email format')
            {
              return;
            }
            
            if (!date) 
            {
                seterror("Please select a date.");
                return;
            }
    
            if (time === "--Select time--") 
            {
                seterror("Please select a time slot.");
                return;
            }
    
            if(!members)
            {
                seterror("Please enter number of members");
                return;
            }
        
            if (members <= 0 || !Number.isInteger(Number(members))) 
            {
                seterror("Please enter a valid number of members (greater than 0).");
                return;
            }
    
            seterror('');
    
            try
            {
                console.log(u);
                const result = await reserveTable({uid:u,members,date,time});
                if (result?.data && (result?.data?.msg === 'Table reserved successfully and email sent!' || result?.data?.msg === 'Email sending failed'))
                {
                  setr(true);
                }
                else
                {
                  seterror(result?.data?.msg || 'Cannot reserve up at the moment');
                }
            }
            catch(err)
            {
                seterror("Cannot reserve at the moment")
            }
            setu(null);
            setmembers('');
            setdate('');
            settime('');
            seta(false);
        }
      
    return (
        <>
            <div id={style.main}>
            <div className={style['header-bar']}>
              <h1 className={style['header-bar-h1']}>Fusion Bytes - Admin : ADD Reservation</h1>
            </div>

                    <>
                            <div className={style['form-container']}>
                                <h2>Fill the Form for Reservation</h2>
                                {a && <Useremail email={email} fun={setu} />}
                                <form>
                                <div className={style['form-group']}>
                                    <label htmlFor="email">email:</label>
                                    <input type="email" id="email" name="email" value={email} onChange={(e)=>{setemail(e.target.value); seterror('')}}/>
                                    </div>
                                    <div className={style['form-group']}>
                                        <label htmlFor="date">Date:</label>
                                        <input type="date" id="date" name="date" value={date} onChange={(e)=>{setdate(e.target.value); seterror('')}}/>
                                    </div>
                                    <div className={style['form-group']}>
                                        <label htmlFor="time">Time Slot:</label>
                                        <select id="time" name="time" value={time} onChange={(e)=>{settime(e.target.value); seterror('')}}>
                                            <option>--Select time--</option>
                                            <option value="17:00-18:00">5:00 PM</option>
                                            <option value="18:00-19:00">6:00 PM</option>
                                            <option value="19:00-20:00">7:00 PM</option>
                                            <option value="20:00-21:00">8:00 PM</option>
                                            <option value="21:00-22:00">9:00 PM</option>
                                            <option value="22:00-23:00">10:00 PM</option>
                                            <option value="23:00-24:00">11:00 PM</option>
                                        </select>
                                    </div>
                                    <div className={style['form-group']}>
                                        <label htmlFor="members">Number of Members:</label>
                                        <input type="number" min="1" step="1" id="members" name="members" value={members} onChange={(e)=>{setmembers(e.target.value); seterror('')}} />
                                    </div>
                                    {error && <p style={{color:'red'}}>{error}</p>}
                                    <button type="button" className={style['reserve-btn']} onClick={() =>navigate('/')}>Back</button>
                                    <button type="button" className={style['reserve-btn']} onClick={() =>{seterror(''); validateEmail(email)}}>Reserve Now</button>
                                </form>
                            </div>
                    </>
                
            </div>
        </>
    );
}

export default Addreservation;