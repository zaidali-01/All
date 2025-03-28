import style from './Home.module.css';
import { useNavigate } from 'react-router-dom';
import img1 from "./images/gallery_image1.jpg";
import img2 from "./images/gallery_image2.jpg";
import img3 from "./images/gallery_image3.jpg";
import img4 from "./images/gallery_image4.jpg";
import img5 from "./images/gallery_image5.png";
import img6 from "./images/gallery_image6.jpg";

function Home(props)
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
        <nav className={style['nav-bar']}>
          <ul className={style['nav-bar-ul']}>
            <li className={style['nav-bar-ul-li']} onClick={() => navigate('/')}><a className={style['nav-bar-ul-li-a']}>Home</a></li>
            <li className={style['nav-bar-ul-li']} onClick={() => navigate('/aboutus')}><a className={style['nav-bar-ul-li-a']}>About Us</a></li>
            <li className={style['nav-bar-ul-li']} onClick={() => navigate('/reservation')}><a className={style['nav-bar-ul-li-a']}>Reservation</a></li>
            <li className={style['nav-bar-ul-li']} onClick={() => navigate('/menu')}><a className={style['nav-bar-ul-li-a']}>Menu</a></li>
            <li className={style['nav-bar-ul-li']} onClick={handleLogout}><a className={style['nav-bar-ul-li-a']}>Log Out</a></li>
          </ul>
        </nav>

        <div className={style['content']}>
          <h1 className={style['content-h1']}>Welcome to Fusion Bytes</h1>
          <p className={style['content-p']}>Enjoy the finest dining experience with exquisite dishes crafted just for you.</p>
          <p className={style['content-p']}>Relax in our cozy atmosphere and let us make your visit unforgettable.</p>
          <button className={style['reserve-btn']} onClick={()=>navigate('/reservation')}>Reserve A Table Now</button>
        </div>

        <div className={style['gallery']}>
          <h2 className={style['gallery-h2']} >Gallery</h2>
          <div className={style['gallery-grid']}>
            <div className={style['gallery-grid-item']}><img className={style['gallery-grid-img']} src={img1} alt="Gallery 1" /></div>
            <div className={style['gallery-grid-item']}><img className={style['gallery-grid-img']} src={img2} alt="Gallery 2" /></div>
            <div className={style['gallery-grid-item']}><img className={style['gallery-grid-img']} src={img3} alt="Gallery 3" /></div>
            <div className={style['gallery-grid-item']}><img className={style['gallery-grid-img']} src={img4} alt="Gallery 4" /></div>
            <div className={style['gallery-grid-item']}><img className={style['gallery-grid-img']} src={img5} alt="Gallery 5" /></div>
            <div className={style['gallery-grid-item']}><img className={style['gallery-grid-img']} src={img6} alt="Gallery 6" /></div>
          </div>
        </div>
      </div>
    </>
  );
}

export default Home;