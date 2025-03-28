import { useEffect, useState } from 'react';
import style from './Login.module.css';
import { useNavigate } from 'react-router-dom';
import { useLoginUserMutation } from '../rtkquery/Api';

function Login(props)
{
  const [userLogin, {data:u,isLoading,isSuccess}] = useLoginUserMutation();
  const [login,setlogin] = useState(false);
  const [email,setemail] = useState('');
  const [password,setpassword] = useState('');
  const [error,seterror] = useState('');
  const navigate = useNavigate();

  useEffect(()=>{if(u) localStorage.setItem("u",JSON.stringify(u))},[u]);
  useEffect(()=>{if(isSuccess && login){props?.setl(true); setTimeout(()=>navigate('/'),100)}},[isSuccess,u,login,navigate]);

  const loginhandle = async (e) =>
  {
    e.preventDefault();
    try
    {
      const result = await userLogin({email,password});
      if (result?.data && result.data?.msg === 'user loginned!')
      {
        setlogin(true);
      }
      else
      {
        seterror(result?.data?.msg || "Invalid email or password");
      }
    }
    catch(err)
    {
      seterror('Cannot Login at the moment');
    }
  } 

  return (
    <>
      <div id={style.main}>
        <div className={style['header-bar']}>
          <h1 className={style['header-bar-h1']}>Fusion Bytes</h1>
        </div>
        <div className={style["form-container"]}>
          <h2 className={style["form-container-h2"]}>Login for Cafe</h2>
          <form onSubmit={loginhandle}>
            <div className={style["form-group"]}>
              <label htmlFor="email">Email:</label>
              <input type="email" id="email" name="email" placeholder="Enter email" value={email} onChange={(e)=>{setemail(e.target.value); seterror('')}}/>
            </div>
            <div className={style["form-group"]}>
              <label htmlFor="password">Password:</label>
              <input type="password" id="password" name="password" placeholder="Enter password" value={password} onChange={(e)=>{setpassword(e.target.value); seterror('')}}/>
            </div>
            {error && <p style={{color:'red'}}>{error}</p>}
            <button type="submit" onClick={()=>seterror('')}>Login</button>
          </form>
          <div className="signup-link">
            <p>Don't have an account! <span onClick={()=>navigate('/register')}>Sign up</span></p>
          </div>
        </div>
      </div>
    </>
  );
}

export default Login;