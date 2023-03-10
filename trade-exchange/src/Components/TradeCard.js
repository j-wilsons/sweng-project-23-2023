import Button from 'react-bootstrap/Button';
import Card from 'react-bootstrap/Card';
import IBMImg from "../Images/IBM.jpg"
import { useEffect, useState } from "react";
import PropTypes from "prop-types";

var amount = 0;
var shares = 0;

const buyShares = () => {
    amount = document.getElementById("amount").value;
    shares = document.getElementById("shares").value;
    console.log("Buying " + amount + " shares of " + shares);
  };
  
  const sellShares = () => {
    amount = document.getElementById("amount").value;
    shares = document.getElementById("shares").value;
    console.log("Selling " + amount + " shares of " + shares);
  };

function TradeCard(props) {
    const [show, setShow] = useState(false);

  const closeHandler = (e) => {
    setShow(false);
    props.onClose(false);
  };

  useEffect(() => {
    setShow(props.show);
  }, [props.show]);

  return (
    <div
      style={{
        visibility: show ? "visible" : "hidden",
        opacity: show ? "1" : "0"
      }}
      className="popup"
    >
    <Card>
      <Card.Body >
        <div className ="row">
      <img src={IBMImg}  alt="horse" style={{ width: 170, height: 150 }} ></img>
        <button
        className="buyButton" variant="primary" size="lg" 
        onClick={() => {
          buyShares();
        }}
      >
        Buy
      </button>
      <button
        className="sellButton" variant="primary" size="lg"
        onClick={() => {
          sellShares();
        }}
      >
        Sell
      </button>
     
        </div>
        <div>
            <Card.Text className="card-text">
                $130.57  
            </Card.Text>
        </div>
        <div>
        <hr style={{width: 450, height: 0.5, background: 'black'}}/>
        </div>
        <div className ="row2">
            <div className="left-text">
        <Card.Text >
          Name : &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; IBM 
        </Card.Text>
        </div>
        </div>
        <div className ="row2">
            <div className="left-text">
        <Card.Text >
          Exchange :&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;NYSTE
        </Card.Text>
        </div>
        </div>
        <div className ="row2">
        <div className="left-text">
        <Card.Text >
          IPO:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1915-11-11
        </Card.Text>
        </div>
        </div>
        <hr style={{width: 450, height: 0.5, background: 'black'}}/>
      </Card.Body>
    </Card>
    </div>
  );
}

export default TradeCard;
    