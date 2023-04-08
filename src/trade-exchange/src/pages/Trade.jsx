import React from "react";
import "../css/Main.css";
import "../css/Text.css";
import NavBar from "../Components/NavBar";
import TradeCard from "../Components/TradeCard";
import StockRow from "../Components/StockRow"
// import PropTypes from "prop-types";
import { useState } from "react";
import { useEffect } from "react";
import { MultiColumnComboBox } from "@progress/kendo-react-dropdowns";
import { equities } from "../Components/Equities";
import { orderType } from "../Components/Equities"
import "@progress/kendo-theme-default/dist/all.css";
import 'bootstrap/dist/css/bootstrap.min.css';
import Button from "react-bootstrap/esm/Button";
import ApexChart from "../Components/stockChart";
import axios from "axios";
var amount = 0;
var shares = 0;
var nameO = ""
var orderT = ""
let myData; // variable to hold response from backend

const buyShares = () => {
  const amount = document.getElementById("amount").value;
  const shares = document.getElementById("shares").value;
  console.log("Buying " + amount + " shares of " + shares);
  
  //get data from backend
  //example for get request
  //prints out whatever is in the response
  fetch("http://localhost:1234/trade", {
    mode: 'no-cors',      // <---- for CORS, do not delete
    method: "POST",       // for post request

    //set the body of the request to the data we want to send
    //key-value pairs
    body: JSON.stringify({
      side: "buy",
      ordertype: "Market",
      amount: amount,
      ticker: shares,
      progress: 0,
      completed: false,
    }),
    //set the content type
    headers: {
      "Content-type": "application/json;"
    }
  })
};
const sellShares = () => {
  amount = document.getElementById("amount").value;
  shares = document.getElementById("shares").value;
  console.log("Selling " + amount + " shares of " + shares);

  //post data to backend
  fetch("http://localhost:1234/trade", {
    mode: 'no-cors',      // <---- for CORS, do not delete
    method: "POST",       // for post request

    //set the body of the request to the data we want to send
    //key-value pairs
    body: JSON.stringify({
      side: "sell",
      ordertype: "Market",
      amount: amount,
      ticker: shares,
      progress: 0,
      completed: false,
    }),
    //set the content type
    headers: {
      "Content-type": "application/json;"
    }
  })
  
};

const columns = [
  {
    field: "symbol",
    header: "Symbol",
    width: "100px",
  },
  {
    field: "name",
    header: "Name",
    width: "100px",
  },
  {
    field: "price",
    header: "Price",
    width: "100px",
  },
];

const orderTypes = [
  {
    field: "nameO",
    header: "Order Type",
    width: "300px"
  }
]

export const Trade = () => {
  const [isShown, setIsShown] = useState(false);
  const [isPriceShown, setIsPriceShown] = useState(false);
  const [price, setPrice] = useState("0")
  const [orderList, setOrderList] = useState([]);
  const [visibility, setVisibility] = useState(false);

  const getInfo = event => {
    shares = document.getElementById("shares").value;
    setIsShown(current => !current);
    }
const getPrice = event => {
  if(orderT === "Limit") {
  setIsPriceShown(current => !current);
}
}
  const popupCloseHandler = (e) => {
    setVisibility(false);
  };
  const [size, setSize] = React.useState("medium");
  const [fillMode, setFillMode] = React.useState("solid");
  const [rounded, setRounded] = React.useState("small");

  const updatePrice = price => {
    this.setState({
      price: this.state.price
    })
  }

  useEffect(() => {
    const element = document.querySelector("#EqList");
    console.log(element);
  }, []);

  return (
    <div className="home">
      <NavBar />
      <div className="right-pos">
        <div>
          <h2>MAKE A TRADE</h2>
          <div>
            <input
              type="text"
              id="amount"
              placeholder="Select quantity ..."
              rounded={rounded}
              style={{
                width: "300px",
                height: "27px",
                fontSize: 15
              }}
            />
            <div
              style={{
                justifyContent: "space-around",
              }}
            >
              <MultiColumnComboBox
                style={{
                  width: "300px",
                }}
                data={equities}
                columns={columns}
                textField={"symbol"}
                size={size}
                fillMode={fillMode}
                rounded={rounded}
                id="shares"
                placeholder="Select share ..."
                
              />
            </div>
            <div 
    style={{
      
      justifyContent: "space-around"
    }}>
      <MultiColumnComboBox
      
        style={{
          width: "300px",
        }}
        data={orderType}
        columns={orderTypes}
        textField={"nameO"}
        size={size}
          fillMode={fillMode}
          rounded={rounded}
          id="nameO"
          orderT={nameO}
        placeholder="Select type ..."
        onChange={() => {
          orderT = document.getElementById("nameO").value
          console.log("OT " + orderT)
          getPrice()
         }}
        
      />
     </div> 
     {isPriceShown ?
     <div>
     <input
        type="text"
        id="price"
        placeholder="Select price ..."
        rounded={rounded}
        price={price}
        style={{
          width: "300px",
          height: "27px",
          fontSize: 15
          
        }}
      />
    </div>
: null}
            <br />
            <div className="row2" 
            style={{ marginLeft: -2}}>
            <button
        className="buyButton" 
        variant="primary" 
        size="lg" 
        style={{backgroundColor: 'yellow'}}
        onClick={() => {
          getInfo();
          
        }}
      >
        Info
      </button>
              <button
                className="buyButton"
                variant="primary"
                size="lg"
                onClick={() => {
                  buyShares();
                }}
              >
                Buy
              </button>
              <button
                className="sellButton"
                variant="primary"
                size="lg"
                onClick={() => {
                  sellShares();
                }}
              >
                Sell
              </button>
            </div>
          </div>
        </div>

      
      
        {isShown ? (
       <div className="left-pos" >
       <div className="container" >
         <table className="table mt-3" style={{color: 'white'}}>
           <thead>
             <tr>
               <th>Ticker</th>
               <th>Price</th>
               <th>Change</th>
               <th>Date</th>
             </tr>
           </thead>
           <tbody>
             <StockRow ticker={shares} />
           </tbody>
         </table>
       </div>
     
       </div>
    ): null }
    </div> 
   
      {visibility ? (
         <div>
      <TradeCard onClose={popupCloseHandler}
        show={visibility} title={Trade} />
          </div>
          ): null }
    </div>
  );
};
