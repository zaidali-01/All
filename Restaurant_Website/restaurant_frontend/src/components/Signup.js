import { useEffect, useState } from 'react';
import style from './Signup.module.css';
import {useAddUsersMutation} from '../rtkquery/Api.js';
import { useNavigate } from 'react-router-dom';

function Signup() 
{
  const navigate = useNavigate();
  const [createUser, {isLoading, isSuccess}] = useAddUsersMutation();
  const [signup,setsignup] = useState(false);
  const [name,setname] = useState('');
  const [email,setemail] = useState('');
  const [pass1,setpass1] = useState('');
  const [pass2,setpass2] = useState('');
  const [error,setError] = useState('');

  useEffect(()=>{(isSuccess && signup) && navigate('/login')},[isSuccess,signup]);

  const validateEmail = (email) =>
  {
    const emailPattern = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
    return emailPattern.test(email);
  }

  const validateName = (name) => 
  {
    const namePattern = /^[A-Za-z\s]+$/;
    return namePattern.test(name) && name.trim().length > 0;
  };

  const signhandle = async (e) =>
  {
    e.preventDefault();
    
    if (!name) 
    {
      setError('Name is required');
      return;
    }
    
    if(!validateName(name))
    {
      setError('Name should only contain alphabets and spaces');
      return;
    }

    if (!validateEmail(email)) 
    {
      setError('Invalid email format');
      return;
    }

    if (pass1.length < 6) 
    {
      setError('Password must be at least 6 characters long');
      return;
    }

    if (pass1 !== pass2) 
    {
      setError('Passwords do not match');
      return;
    }

    try
    {
      const result = await createUser({name,email,password:pass1});
      if (result?.data && result.data?.msg === 'User registered successfully and email sent!') 
      {
        setsignup(true);
      }
      else
      {
        setError(result?.error?.data?.msg || 'Cannot sign up at the moment');
      }
    }
    catch(err)
    {
      setError('Cannot sign up at the moment');
    }
  }

  return (
    <>
      <div id={style.main}>
        <div className={style['header-bar']}>
          <h1 className={style['header-bar-h1']}>Fusion Bytes</h1>
        </div>
        <div className={style["form-container"]}>
          <h2 className={style["form-container-h2"]}>Sign Up for Cafe</h2>
          <form onSubmit={signhandle}>
            <div className={style["form-group"]}>
              <label htmlFor="name">Name:</label>
              <input type="text" id="name" name="name" placeholder="Enter name" value={name} onChange={(e)=>{setname(e.target.value); setError('')}}/>
            </div>
            <div className={style["form-group"]}>
              <label htmlFor="email">Email:</label>
              <input type="email" id="email" name="email" placeholder="Enter email" value={email} onChange={(e)=>{setemail(e.target.value); setError('')}}/>
            </div>
            <div className={style["form-group"]}>
              <label htmlFor="password">Password:</label>
              <input type="password" id="password" name="password" placeholder="Enter password" value={pass1} onChange={(e)=>{setpass1(e.target.value); setError('')}}/>
            </div>
            <div className={style["form-group"]}>
              <label htmlFor="confirmPassword">Confirm Password:</label>
              <input type="password" id="confirmPassword" name="confirmPassword" placeholder="Confirm password" value={pass2} onChange={(e)=>{setpass2(e.target.value); setError('')}}/>
            </div>
            {error && <p style={{color:'red'}}>{error}</p>}
            <button type="submit" onClick={()=>setError('')}>Sign Up</button>
          </form>
          <div className={style['login-link']}>
            <p>Already have an account! <span onClick={() => navigate('/login')}>Login</span></p>
          </div>
        </div>
      </div>
    </>
  );
}

export default Signup;