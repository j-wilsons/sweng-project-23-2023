import React from "react";
import "../css/Main.css";
import "../css/Text.css";
import NavBar from "../Components/NavBar";
import TradeCard from "../Components/TradeCard";
import StockRow from "../Components/StockRow"
import PieChart from "../Components/PieChart";
import OrderPlotter from "../Components/OrderPlotter"
// import PropTypes from "prop-types";
import { useState } from "react";
import { useEffect } from "react";
import { MultiColumnComboBox } from "@progress/kendo-react-dropdowns";
import { equities } from "../Components/Equities";
import { orderType } from "../Components/Equities"
import { Button } from "react-bootstrap";
import { Modal } from "react-bootstrap";
import 'react-awesome-button/dist/styles.css';
import "@progress/kendo-theme-default/dist/all.css";
import 'bootstrap/dist/css/bootstrap.min.css';
import axios from "axios";
var amount = 0;
var shares = 0;
var nameO = ""
var orderT = ""
let myData; // variable to hold response from backend


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
  const [price, setPrice] = useState('')
  const [lmtPrice, setlmtPrice] = useState('')
  const [type, setType] = React.useState('Market')
  const [orderPlList, setOrderPlList] = useState([]);
  const [order, setOrder] = useState(null);
  const [modalShow, setModalShow] = React.useState(false);

  const API_KEY2 = '642170e62900b1.66857007'
  let API_Call2 = `https://eodhistoricaldata.com/api/real-time/${shares}.US?fmt=json&api_token=${API_KEY2}`
  
;

function MyModal(props) {
  return (
    <Modal
      {...props}
      size="lg"
      aria-labelledby="contained-modal-title-vcenter"
      centered
    >
      <Modal.Header closeButton>
        <Modal.Title id="contained-modal-title-vcenter">
          Orders Executed
        </Modal.Title>
      </Modal.Header>
      <Modal.Body>
      <PieChart chartData={chartData}  />
      </Modal.Body>
      <Modal.Footer>
        <Button onClick={props.onHide}>Close</Button>
      </Modal.Footer>
    </Modal>
  );

}
    const changePriceMkt = () => 
   
    console.log("change price " + shares)
    {fetch(API_Call2)
      .then((response) => response.json())
      
      .then((data2) => {
          setPrice(( data2.close))
          
      })
    }
   
  const buyShares = () => {
    const amount = document.getElementById("amount").value;
    const shares = document.getElementById("shares").value;
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
    
    console.log("Buying " + amount + " shares of " + shares + " at" + price);
    if(lmtPrice != ""){
      handleAddLmtOrder();
      }
      else {
        handleAddOrder();
      }
  }
  const sellShares = () => {
    amount = document.getElementById("amount").value;
    shares = document.getElementById("shares").value;
    console.log("Selling " + amount + " shares of " + shares );
  
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
    if(lmtPrice == ''){
    handleAddSellOrder();
    }
    else {
      handleAddSellLmtOrder();
    }
  };
const handleAddOrder = () => {
  const amount = document.getElementById("amount").value;
  shares = document.getElementById("shares").value;
  setOrder(("  " + shares + "     Mkt Buy    "  + price + "    " + amount + "        10/04/23    Filled"));
  setOrderPlList([...orderPlList, order]);
  setlmtPrice('')
};
const handleAddSellOrder = () => {
  const amount = document.getElementById("amount").value;
  shares = document.getElementById("shares").value;
  setOrder(("  " + shares + "     Mkt Sell    "  + price + "    " + amount + "        10/04/23    Filled"));
  setOrderPlList([...orderPlList, order]);
  
};
const handleAddLmtOrder = () => {
  const amount = document.getElementById("amount").value;
  shares = document.getElementById("shares").value;
  setOrder(("  " + shares + "     Lmt Buy    "  + lmtPrice + "    " + amount + "        10/04/23    Filled"));
  setOrderPlList([...orderPlList, order]);
  
};
const handleAddSellLmtOrder = () => {
  const amount = document.getElementById("amount").value;
  shares = document.getElementById("shares").value;
  setOrder(("  " + shares + "     Lmt Sell    "  + lmtPrice + "    " + amount + "        10/04/23    Filled"));
  setOrderPlList([...orderPlList, order]);
  
};


  const getInfo = event => {
    shares = document.getElementById("shares").value;
    setIsShown(current => !current);
    }
const getPrice = event => {
  if(event === "Limit") {
  setIsPriceShown(current => !current);
  
}
setlmtPrice('')
}
const [chartData, setChartData] = useState({
  labels: ["Shares Processed", "Shares Left"],
  datasets: [
    {
      data: [
        20,
        80,
      ],
      backgroundColor: ["rgba(40,245,40,1)", "rgba(255,0,0,1)"],
      borderColor: "black",
      borderWidth: 2,
    }
  ]
})
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
                onChange={() => {
                  changePriceMkt();}}
              />
            </div>
            

      <MyModal
        show={modalShow}
        onHide={() => setModalShow(false)}
      />
            <div 
    style={{
      
      justifyContent: "space-around"
    }}>
      
     </div> 
     {isPriceShown ? 
      
     <div>
     <input
        type="text"
        id="price"
        placeholder="Select price..."
        onChange={(e) => setlmtPrice(e.target.value)}
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
            <Button
            style={{
              backgroundColor: 'yellow',
              color: 'black',
              width: 90,
              height: 40
            }}
        onClick={() => {
          getInfo();
          
        }}
      >
        Info
      </Button>
              <Button
                style={{
                  backgroundColor: 'aquamarine',
                  color: 'black',
                  width: 90,
                  height: 40
                }}
                onClick={() => {
                  buyShares();
                }}
              >
                Buy
              </Button>
              <Button
                style={{
                  backgroundColor: 'red',
                  color: 'white',
                  width: 90,
                  height: 40
                }}
                onClick={() => {
                  sellShares();
                }}
              >
                Sell
              </Button>
              <div>
              <Button
                style={{
                  backgroundColor: 'aquamarine',
                  color: 'black',
                  width: 90,
                  height: 40,
                  marginTop: 50,
                  marginLeft: -180
                }}
                onClick={() => {
                  getPrice("Limit");
                 
                }}
              >
                Limit
              </Button>
              <Button
                style={{
                  backgroundColor: 'red',
                  color: 'white',
                  width: 90,
                  height: 40,
                  marginTop: 50
                }}
                onClick={() => {
                  getPrice("Market");
                 setIsPriceShown(false)
                }}
              >
                Market
              </Button>
              </div>
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
   <div className="right-corner-pos">
   <div style={{color: 'white'}}>
      <h2>Order Plotter</h2>
      <thead>
             <tr>
               <th>Ticker</th>
               <th>Type</th>
               <th>Price</th>
               <th>Amount</th>
               <th>Date</th>
               <th>Status</th>
             </tr>
           </thead>
           {order ? (
            <div>
      <input type="text" value={order} onChange={(e) => setOrder(e.target.value)} style={{width: "400px", backgroundColor: 'yellow'}}/>
      <button onClick={() => setModalShow(true)} style={{marginLeft: -60, backgroundColor: 'yellow' }}>Status</button>
        {orderPlList.map((order, index) => (
          <div>
            <input value={order} style={{width: "400px"}} />,
            <button onClick={() => setModalShow(true)} style={{marginLeft: -60}}>Status</button>
            </div>
        ))}
    
        </div>
           ): null }
    </div>
   </div>
      
    </div>
  );
};
