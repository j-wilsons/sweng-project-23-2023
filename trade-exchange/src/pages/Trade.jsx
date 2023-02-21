import "../css/Main.css";
import "../css/Text.css";

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
  return (
    <div className="center center-text">
      <h1>Trade</h1>
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
        className="center-text"
        onClick={() => {
          buyShares();
        }}
      >
        Buy
      </button>
      <button
        className="center-text"
        onClick={() => {
          sellShares();
        }}
      >
        Sell
      </button>
    </div>
  );
};
