import React, { useState } from 'react';

function OrderPlotter() {
  const [orderList, setOrderList] = useState([]);
  const [order, setOrder] = useState('');

  const handleAddOrder = () => {
    setOrderList([...orderList, order]);
    setOrder('');
  };

  const handleDeleteOrder = (index) => {
    const newOrderList = [...orderList];
    newOrderList.splice(index, 1);
    setOrderList(newOrderList);
  };

  return (
    <div>
      <h1>Order Plotter</h1>
      <input type="text" value={order} onChange={(e) => setOrder(e.target.value)} />
      <button onClick={handleAddOrder}>Add Order</button>
      <ul>
        {orderList.map((order, index) => (
          <li key={index}>
            {order} <button onClick={() => handleDeleteOrder(index)}>Delete</button>
          </li>
        ))}
      </ul>
    </div>
  );
}

export default OrderPlotter;
