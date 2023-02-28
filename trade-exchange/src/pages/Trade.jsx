import "../css/Main.css";
import "../css/Text.css";
import NavBar from "../Components/NavBar";
import TradeCard from "../Components/TradeCard"
import PropTypes from "prop-types";
import { useState } from "react";


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


export const Trade = () => {
  const [visibility, setVisibility] = useState(false);

const popupCloseHandler = (e) => {
  setVisibility(false);
};
  return (

    <div className="home">
    <NavBar />
    <div>
      <h2 className="card-text">
        Welcome back, user
      </h2>
      <h2 className="main-text">
         $10,000
      </h2>
      <h2 style= {{ color: '#45c393', font: 'Times New Roman', marginLeft: 650}}>
        +0% last week.
      </h2> 
    </div>
    <div className="center">
      <h2>Make a Trade</h2>
      <input
        className="center-text"
        type="text"
        id="amount"
        placeholder="How many shares?"
      />
      <input
        className="center-text"
        type="text"
        id="shares"
        placeholder="Which share?"
      />
      <br />
      <button
        className="button" variant="primary" size="lg"
        onClick={() => {
          setVisibility(true)
        }}
      >
        Go
      </button>
    </div>
    <div>
    <TradeCard  onClose={popupCloseHandler}
        show={visibility} title={Trade}>
          Go now </TradeCard>
    </div>
    </div>
           
       
    );
};
