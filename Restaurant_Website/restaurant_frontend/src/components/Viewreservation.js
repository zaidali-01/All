import style from './Viewreservation.module.css';
import Order from './Order.js'
import { useNavigate } from 'react-router-dom';
import { useGetAllReservationsQuery } from '../rtkquery/Api';
import { useState } from 'react';

function Viewreservation() 
{
  const {data,isSuccess} = useGetAllReservationsQuery();
  const [order,setorder] = useState(false);
  const [r,setr] = useState('');
  const navigate = useNavigate();
  return (
    <>
    {order ? <Order fun={setorder} reserve={r} />
    :<>
      <div id={style.main}>
        <div className={style['header-bar']} style={{marginBottom:"10px"}}>
          <h1 className={style['header-bar-h1']}>Fusion Bytes - Admin : view reservation</h1>
        </div>
      </div>
        {isSuccess && data?.reserve.map((a,index)=><div key={index} style={{marginTop:"8%",display:"flex", width:"65%",backgroundColor:"rgb(176, 167, 155)",padding:"10px",borderRadius:"5px"}}><p style={{marginRight:"30px", marginLeft:"20px"}}>Email: {a?.email}</p><p style={{marginRight:"30px"}}>Date: {new Date(a?.date).toLocaleDateString('en-US', { year: 'numeric', month: '2-digit', day: '2-digit' })}</p><p style={{marginRight:"30px"}}>Time: {a?.time}</p><p>Members: {a?.members}</p><button onClick={() =>{setr(a); setorder(true)}} style={{ marginLeft: "60px", padding: "10px", zIndex:"10" }}>Order</button><br></br></div>)}
        <button style={{marginLeft:"10px", marginTop:"20px", marginRight:"10px", zIndex:"20"}} onClick={()=>navigate('/')}>Back</button>
        <button onClick={()=>navigate('/addreservation')} style={{zIndex:"20", marginBottom:"20px"}}>Add Reservation</button>
    </>}
    </>
  );
}

export default Viewreservation;