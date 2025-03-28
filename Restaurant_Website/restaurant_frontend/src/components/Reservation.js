import style from './Reservation.module.css';
import { useState, useEffect } from 'react';
import { useNavigate } from 'react-router-dom';
import { useGetReservationsByIdQuery, useReserveTableMutation } from '../rtkquery/Api';
import { jwtDecode } from 'jwt-decode';
import Order from './Order';

function View(props)
{
    const {data,isSuccess} = useGetReservationsByIdQuery(props?.uid);
    const [order,setorder] = useState(false);
    const [r,setr] = useState('');
    return (<>{order ? <Order fun={setorder} reserve={r} /> :
        <>
         {isSuccess && data?.reserve.map((a,index)=><div key={index} style={{marginTop:"10%",display:"flex", width:"45%",backgroundColor:"rgb(176, 167, 155)",padding:"10px",borderRadius:"5px"}}><p style={{marginRight:"30px", marginLeft:"20px"}}>Date: {new Date(a?.date).toLocaleDateString('en-US', { year: 'numeric', month: '2-digit', day: '2-digit' })}</p><p style={{marginRight:"30px"}}>Time: {a?.time}</p><p>Members: {a?.members}</p><button onClick={()=>{setr(a); setorder(true)}} style={{ marginLeft: "60px", padding: "10px", zIndex:"10" }}>Order</button><br></br></div>)}
        <button onClick={() => props?.fun(true)}>Add New Reservation</button>
        </>}
        </>
        );
}

function Reservation(props)
{
    const [reserveTable, {isLoading,isSuccess}] = useReserveTableMutation();
    const [reserve, setReserve] = useState(true);
    const [date,setdate] = useState('');
    const [time,settime] = useState('');
    const [members,setmembers] = useState(null);
    const [error,seterror] = useState('');
    const [u,setu] = useState(null);
    const [r,setr] = useState(false);
    const navigate = useNavigate();

    useEffect(()=>{const saved =localStorage.getItem("u") || "";
        const token= JSON.parse(saved); if(token){setu(jwtDecode(token?.token))}},[]);
    useEffect(()=>{(isSuccess && r) && setReserve(false)},[isSuccess,r]);

    const handleLogout = () => 
    {
        localStorage.removeItem('u');
        props?.setl(false);
        props?.setu(null);
        navigate('/login');
    };
      
    const handlereserve = async (e) =>
    {
        e.preventDefault(); 

        if (!date) 
        {
            seterror("Please select a date.");
            return;
        }

        if (!time) 
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
            const result = await reserveTable({uid:u?.uid,members,date,time});
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
        setdate('');
        settime('');
        setmembers(null);
    }
  
    return (
        <>
            <div id={style.main}>
                <div className={style['header-bar']}>
                    <ul>
                        <li onClick={() => navigate('/')}><a>Home</a></li>
                        <li onClick={() => navigate('/aboutus')}><a>About Us</a></li>
                        <li onClick={() => navigate('/reservation')}><a>Reservation</a></li>
                        <li onClick={() => navigate('/menu')}><a>Menu</a></li>
                        <li onClick={handleLogout}><a>Log Out</a></li>
                    </ul>
                </div>
                {reserve ? (
                            <div className={style['form-container']}>
                                <h2>Fill the Form for Reservation</h2>
                                <form onSubmit={handlereserve}>
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
                                        <input type="number" min="1" step="1" id="members" name="members" value={members} onChange={(e)=>{setmembers(e.target.value); seterror('')}}/>
                                    </div>
                                    {error && <p style={{color:'red'}}>{error}</p>}
                                    <button onClick={()=>{setReserve(false); setdate(''); settime(''); setmembers(null)}}>Show Reservations</button>
                                    <button type="submit" className={style['reserve-btn']} onClick={()=>seterror('')}>Reserve Now</button>
                                </form>
                            </div>
                        ) : (
                            <View uid={u?.uid} fun={setReserve} />
                )}
            </div>
        </>
    );
}

export default Reservation;