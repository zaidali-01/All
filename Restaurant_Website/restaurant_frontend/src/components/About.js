import style from './About.module.css';
import { useNavigate } from 'react-router-dom';

function About(props) 
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
        <ul className={style['nav-bar-ul']}> 
          <li className={style['nav-bar-ul-li']} onClick={() => navigate('/')}>
            <a className={style['nav-bar-ul-li-a']}>Home</a> 
          </li>
          <li className={style['nav-bar-ul-li']} onClick={() => navigate('/aboutus')}>
            <a className={style['nav-bar-ul-li-a']}>About Us</a> 
          </li>
          <li className={style['nav-bar-ul-li']} onClick={() => navigate('/reservation')}>
            <a className={style['nav-bar-ul-li-a']}>Reservation</a> 
          </li>
          <li className={style['nav-bar-ul-li']} onClick={() => navigate('/menu')}>
            <a className={style['nav-bar-ul-li-a']}>Menu</a>
          </li>
          <li className={style['nav-bar-ul-li']} onClick={handleLogout}>
            <a className={style['nav-bar-ul-li-a']}>Log Out</a> 
          </li>
        </ul>
      </div>

      <div className={style.section} id={style.introduction}> 
        <h1 className={style['section-h1']}>About us</h1>
        <p className={style['section-p']}>
          Welcome to our restaurant! We pride ourselves on delivering a
          dining experience that combines tradition, flavor, and a warm
          atmosphere. Our chefs are dedicated to creating dishes that are
          not only delicious but also celebrate the finest ingredients
          and culinary expertise. Whether you're stopping by for a casual
          meal or celebrating a special occasion, we are committed to making
          your visit memorable. We believe that great food is at the heart of
          every great gathering, and our goal is to make every moment you spend
          here enjoyable and special.
        </p>
      </div>

      <div className={style.section} id={style['what-we-offer']} styles={{backgroundColor:"rgb(176, 167, 155)",color:"black"}}>
        <h1 className={style['section-h1']}>What We Offer</h1>
        <p className={style['section-p']}>
          Our menu is a reflection of our commitment to variety and quality.
          From fast food favorites to traditional desi dishes and savory BBQ,
          we have something for everyone. We use only the freshest ingredients,
          sourced from trusted suppliers, ensuring every bite bursts with
          flavor. Our drinks menu features a wide selection of beverages,
          perfect for pairing with your meal, and our desserts are the ideal
          way to end your dining experience on a sweet note. We also offer a
          cozy ambiance that’s ideal for family dinners, friendly gatherings, or
          just a relaxing meal.
        </p>
      </div>

      <div className={style.section} id={style['contact-us']}>
        <h1 className={style['section-h1']}>Contact Us</h1>
        <p className={style['section-p']}>Phone: (123) 456-7890</p>
        <p className={style['section-p']}>Email: info@restaurant.com</p>
        <p className={style['section-p']}>
          Facebook: <a href="https://facebook.com" className={style['link']}>facebook.com/restaurant</a>
        </p>
        <p className={style['section-p']}>
          Instagram: <a href="https://instagram.com" className={style['link']}>instagram.com/restaurant</a>
        </p>
      </div>
      </div>
    </>
  );
}

export default About;