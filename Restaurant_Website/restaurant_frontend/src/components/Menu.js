import styles from './Menu.module.css';
import {useState,useEffect} from 'react';
import { useNavigate } from 'react-router-dom';
import { useGetMenuByCategoryQuery } from '../rtkquery/Api';

function Menu(props) 
{
    const {data:arr1} = useGetMenuByCategoryQuery('Fast Food');
    const {data:arr2} = useGetMenuByCategoryQuery('Desi Food');
    const {data:arr3} = useGetMenuByCategoryQuery('BBQ');
    const {data:arr4} = useGetMenuByCategoryQuery('Dessert');
    const {data:arr5} = useGetMenuByCategoryQuery('Drinks');

    const navigate = useNavigate();
    const [a,seta] = useState(0);

    useEffect(()=>{setTimeout(()=>seta(a+1),3000)},[a]);

    const handleLogout = () =>
        {
          localStorage.removeItem('u');
          props?.setl(false);
          props?.setu(null);
          navigate('/login');
      };
      
    return (
        <div className={styles.main}>
            <nav className={styles['nav-bar']}>
                <ul className={styles['nav-bar-ul']}>
                    <li className={styles['nav-bar-ul-li']} onClick={() => navigate('/')}><a className={styles['nav-bar-ul-li-a']}>Home</a></li>
                    <li className={styles['nav-bar-ul-li']} onClick={() => navigate('/aboutus')}><a className={styles['nav-bar-ul-li-a']}>About Us</a></li>
                    <li className={styles['nav-bar-ul-li']} onClick={() => navigate('/reservation')}><a className={styles['nav-bar-ul-li-a']}>Reservation</a></li>
                    <li className={styles['nav-bar-ul-li']} onClick={() => navigate('/menu')}><a className={styles['nav-bar-ul-li-a']}>Menu</a></li>
                    <li className={styles['nav-bar-ul-li']} onClick={handleLogout}><a className={styles['nav-bar-ul-li-a']}>Log Out</a></li>
                </ul>
            </nav>
            <div className={styles['categories-container']}>
                <div className={styles.category}>
                    <h2>Fast Food</h2>
                    {
                    <div className={styles.items}>
                        <div className={styles.item}>
                            <img src={`http://localhost:5000/${arr1?.items[a%(arr1?.items.length)]?.path}`} alt="Fast Food Item" />
                            <p>{arr1?.items[a%(arr1?.items.length)]?.name}</p>
                            <p>{arr1?.items[a%(arr1?.items.length)]?.price} pkr</p>
                        </div>
                        <div className={styles.item}>
                            <img src={`http://localhost:5000/${arr1?.items[(a+1)%(arr1?.items.length)]?.path}`} alt="Fast Food Item" />
                            <p>{arr1?.items[(a+1)%(arr1?.items.length)]?.name}</p>
                            <p>{arr1?.items[(a+1)%(arr1?.items.length)]?.price} pkr</p>
                        </div>
                    </div>}
                </div>

                <div className={styles.category}>
                    <h2>Desi Food</h2>
                    <div className={styles.items}>
                        <div className={styles.item}>
                            <img src={`http://localhost:5000/${arr2?.items[a%(arr2?.items.length)]?.path}`} alt="Desi Food Item" />
                            <p>{arr2?.items[a%(arr2?.items.length)]?.name}</p>
                            <p>{arr2?.items[a%(arr2?.items.length)]?.price} pkr</p>
                        </div>
                        <div className={styles.item}>
                            <img src={`http://localhost:5000/${arr2?.items[(a+1)%(arr2?.items.length)]?.path}`} alt="Desi Food Item" />
                            <p>{arr2?.items[(a+1)%(arr2?.items.length)]?.name}</p>
                            <p>{arr2?.items[(a+1)%(arr2?.items.length)]?.price} pkr</p>
                        </div>
                    </div>
                </div>

                <div className={styles.category}>
                    <h2>BBQ</h2>
                    <div className={styles.items}>
                        <div className={styles.item}>
                            <img src={`http://localhost:5000/${arr3?.items[a%(arr3?.items.length)]?.path}`} alt="BBQ Item" />
                            <p>{arr3?.items[a%(arr3?.items.length)]?.name}</p>
                            <p>{arr3?.items[a%(arr3?.items.length)]?.price} pkr</p>
                        </div>
                        <div className={styles.item}>
                            <img src={`http://localhost:5000/${arr3?.items[(a+1)%(arr3?.items.length)]?.path}`} alt="BBQ Item" />
                            <p>{arr3?.items[(a+1)%(arr3?.items.length)]?.name}</p>
                            <p>{arr3?.items[(a+1)%(arr3?.items.length)]?.price} pkr</p>
                        </div>
                    </div>
                </div>

                <div className={styles.category}>
                    <h2>Dessert</h2>
                    <div className={styles.items}>
                        <div className={styles.item}>
                            <img src={`http://localhost:5000/${arr4?.items[a%(arr4?.items.length)]?.path}`} alt="Dessert Item" />
                            <p>{arr4?.items[a%(arr4?.items.length)]?.name}</p>
                            <p>{arr4?.items[a%(arr4?.items.length)]?.price} pkr</p>
                        </div>
                        <div className={styles.item}>
                            <img src={`http://localhost:5000/${arr4?.items[(a+1)%(arr4?.items.length)]?.path}`} alt="Dessert Item" />
                            <p>{arr4?.items[(a+1)%(arr4?.items.length)]?.name}</p>
                            <p>{arr4?.items[(a+1)%(arr4?.items.length)]?.price} pkr</p>
                        </div>
                    </div>
                </div>

                <div className={styles.category}>
                    <h2>Drinks</h2>
                    <div className={styles.items}>
                        <div className={styles.item}>
                            <img src={`http://localhost:5000/${arr5?.items[a%(arr5?.items.length)]?.path}`} alt="Drink Item" />
                            <p>{arr5?.items[a%(arr5?.items.length)]?.name}</p>
                            <p>{arr5?.items[a%(arr5?.items.length)]?.price} pkr</p>
                        </div>
                        <div className={styles.item}>
                            <img src={`http://localhost:5000/${arr5?.items[(a+1)%(arr5?.items.length)]?.path}`} alt="Drink Item" />
                            <p>{arr5?.items[(a+1)%(arr5?.items.length)]?.name}</p>
                            <p>{arr5?.items[(a+1)%(arr5?.items.length)]?.price} pkr</p>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    );
}

export default Menu;