import style from './Admin.module.css';
import { useNavigate } from 'react-router-dom';

function Admin(props) 
{
  const navigate = useNavigate();

  const handleLogout = () =>
    {
      localStorage.removeItem('u');
      props?.setl(false);
      props?.setu(null);
      navigate('/login');
  };

  return (
    <>
      <div id={style.main}>
        <div className={style['header-bar']}>
          <h1 className={style['header-bar-h1']}>Fusion Bytes - Admin</h1>
        </div>

        <div className={style['button-container']}>
          <button className={style['admin-btn']} onClick={() => navigate('/viewreservation')}>View Reservation</button>
          <button className={style['admin-btn']} onClick={() => navigate('/addreservation')}>Add Reservation</button>
          <button className={style['admin-btn']} onClick={() => navigate('/addtable')}>Add Table</button>
          <button className={style['admin-btn']} onClick={() => navigate('/addmenu')}>Add Menu</button>
          <button className={style['admin-btn']} onClick={handleLogout}>Log out</button>
        </div>
      </div>
    </>
  );
}

export default Admin;