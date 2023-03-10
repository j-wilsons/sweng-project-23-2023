import "../App.css";
// import logo from "../logo.svg";
import tradeImg from "../Images/tradingimage.jpg";
import capImg from "../Images/cap.jpg";
import graphImg from "../Images/graph.jpg";

export const Home = () => {
  return (
    <div className="home center-horizontal">
      <div>
        <h1 className="text-animation text-center">
          Get started into trading without risking
          <br/>
          your own money.
        </h1>
        <h3 className="center-horizontal">
          Sign up for a free account to get started
        </h3>
        <div />
        <img src={tradeImg} alt="horse" />
      </div>
      <div>
        <div>
          <img
            src={capImg}
            className="img2"
            alt="horse"
            style={{ width: 50, height: 50 }}
          />
          <img
            src={graphImg}
            className="img3"
            alt="horse"
            style={{ width: 50, height: 50 }}
          />
        </div>
        <div className="row">
          <div>
            <h2 className="mid-text">Learn in a safe environment</h2>
            <h3 className="smaller-text">
              STE allows you to practise paper trading - trading with simulated
              funds.
            </h3>
            <h3 className="smaller-text">
              Sharpen your trading skills at your own pace and when you are
              ready, switch to live trading!
            </h3>
          </div>
          <div>
            <h2 className="mid-text">Get a live market experience</h2>
            <h3 className="smaller-text">
              Trade stocks in real-time on a platform with all the same market
              conditions as real life trading.
            </h3>
            <h3 className="smaller-text">
              STE will automatically execute your orders, showing your actual
              trading results.
            </h3>
          </div>
        </div>
      </div>
    </div>
  );
};
