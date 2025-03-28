import { useState } from 'react';
import style from './Signup.module.css';
import { useNavigate } from 'react-router-dom';
import { useCreateMenuMutation } from '../rtkquery/Api';

function Addmenu() {
  const [createmenu, { isSuccess }] = useCreateMenuMutation();
  const [error, setError] = useState('');
  const [name, setName] = useState('');
  const [category, setCategory] = useState('');
  const [price, setPrice] = useState('');
  const [img, setImg] = useState(null);
  const navigate = useNavigate();

  const validateName = (name) => {
    const namePattern = /^[A-Za-z\s]+$/;
    return namePattern.test(name) && name.trim().length > 0;
  };

  const handleMenu = async (e) => {
    e.preventDefault();

    if (!name) {
      setError('Item name is required');
      return;
    }

    if (!validateName(name)) {
      setError('Item name should only contain alphabets and spaces');
      return;
    }

    if (!category) {
      setError('Category not selected');
      return;
    }

    if (!price) {
      setError('Price not entered');
      return;
    }

    if (price < 0) {
      setError('Invalid price');
      return;
    }

    if (!img) {
      setError('Image not uploaded');
      return;
    }

    try {
      const formData = new FormData();
      formData.append('name', name);
      formData.append('category', category);
      formData.append('price', price);
      formData.append('img', img);

      const result = await createmenu(formData);

      if (result?.data && result.data?.msg === 'Menu Item Added') {
        navigate('/');
      } else {
        setError(result?.error?.data?.msg || 'Cannot add menu at the moment');
      }
    } catch (err) {
      setError('Cannot add menu at the moment');
    }
  };

  return (
    <>
      <div id={style.main}>
        <div className={style['header-bar']}>
          <h1 className={style['header-bar-h1']}>Fusion Bytes</h1>
        </div>
        <div className={style['form-container']}>
          <h2 className={style['form-container-h2']}>Add Menu</h2>
          <form onSubmit={handleMenu}>
            <div className={style['form-group']}>
              <label>Item Name:</label>
              <input
                type="text"
                value={name}
                onChange={(e) => {
                  setName(e.target.value);
                  setError('');
                }}
              />
            </div>
            <div className={style['form-group']}>
              <label>Category:</label>
              <select
                value={category}
                style={{ width: '51%', padding: '8px', border: '1px solid black', borderRadius: '4px' }}
                onChange={(e) => {
                  setCategory(e.target.value);
                  setError('');
                }}
              >
                <option>--Select Category--</option>
                <option value="Fast Food">Fast Food</option>
                <option value="Desi Food">Desi Food</option>
                <option value="BBQ">BBQ</option>
                <option value="Dessert">Dessert</option>
                <option value="Drinks">Drinks</option>
              </select>
            </div>
            <div className={style['form-group']}>
              <label>Price:</label>
              <input
                type="number"
                min="0"
                step="1"
                value={price}
                onChange={(e) => {
                  setPrice(e.target.value);
                  setError('');
                }}
              />
            </div>
            <div className={style['form-group']}>
              <label>Image:</label>
              <input
                type="file"
                accept=".png, .jpg, .jpeg"
                onChange={(e) => setImg(e.target.files[0])}
              />
            </div>
            {error && <p style={{ color: 'red' }}>{error}</p>}
            <button onClick={() => navigate('/')}>Back</button>
            <button type="submit" style={{ marginLeft: '10px' }} onClick={() => setError('')}>
              Add
            </button>
          </form>
        </div>
      </div>
    </>
  );
}

export default Addmenu;
