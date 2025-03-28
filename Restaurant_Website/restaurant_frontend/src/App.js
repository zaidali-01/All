import React, { useEffect, useState } from "react";
import { Navigate, Route, Routes } from "react-router-dom";
import Home from "./components/Home";
import Signup from "./components/Signup";
import Login from "./components/Login";
import About from "./components/About";
import Menu from "./components/Menu";
import Reservation from "./components/Reservation";
import Admin from "./components/Admin";
import Viewreservation from "./components/Viewreservation";
import Addreservation from "./components/Addreservation";
import { jwtDecode } from "jwt-decode";
import Table from "./components/Table";
import Addmenu from "./components/Addmenu";

function App() 
{
  const [u,setu] = useState(null);
  const [load,setload] = useState(true);
  const [l,setl] = useState(false);
  useEffect(()=>{const saved =localStorage.getItem("u");
    if(saved)
    {
    const token= JSON.parse(saved);
    const decodedToken = jwtDecode(token?.token);
    const currentTime = Date.now() / 1000;
    if (decodedToken && decodedToken?.exp > currentTime) 
    {
      setu(decodedToken);
    }
    else
    {
      localStorage.removeItem('u');
    }}
    setload(false);
  },[l]);

  if(load)
  {
    return null;
  }
  return (
    <Routes>
      {u ? <>
      {u?.role!=='admin' ? <>
      <Route path="/" index element={<Home setl={setl} setu={setu} />} />
      <Route path="/aboutus" element={<About setl={setl} setu={setu} />} />
      <Route path="/menu" element={<Menu setl={setl} setu={setu} />} />
      <Route path="/reservation" element={<Reservation setl={setl} setu={setu} />} />
      </> :
      <>
      <Route path="/" index element={<Admin setl={setl} setu={setu} />} />
      <Route path="/viewreservation" element={<Viewreservation />} />
      <Route path="/addreservation" element={<Addreservation />} />
      <Route path="/addtable" element={<Table />} />
      <Route path="/addmenu" element={<Addmenu />} />
      </>}</>
      : <>
      <Route path="/register" element={<Signup />} />
      <Route path="/login" element={<Login setl={setl} />} />
      <Route path="/" index element={<Navigate to="/login" />} />
      </>}
    </Routes>
  );
}

export default App;