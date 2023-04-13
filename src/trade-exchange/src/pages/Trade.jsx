import React from "react";
import "react-awesome-button/dist/styles.css";
import "@progress/kendo-theme-default/dist/all.css";
import "bootstrap/dist/css/bootstrap.min.css";
import "../css/Main.css";
import "../css/Text.css";
import "../css/Flex.css";
import "../css/Grid.css";
// import "../css/Button.css";
import TradeCard from "../Components/TradeCard";
import StockRow from "../Components/StockRow";
import PieChart from "../Components/PieChart";
import Graph from "../Components/Graph";
import OrderPlotter from "../Components/OrderPlotter";
// import PropTypes from "prop-types";
import { useState } from "react";
import { useEffect } from "react";
import { MultiColumnComboBox } from "@progress/kendo-react-dropdowns";
import { equities } from "../Components/Equities";
import { orderType } from "../Components/Equities";
import { Button } from "react-bootstrap";
import { Modal } from "react-bootstrap";
import ButtonGroup from "react-bootstrap/ButtonGroup";
import ToggleButton from "react-bootstrap/ToggleButton";
import axios from "axios";

var amount = 0;
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
    width: "300px",
  },
];

export const Trade = () => {
  const [isShown, setIsShown] = useState(false);
  const [isPriceShown, setIsPriceShown] = useState(false);
  const [price, setPrice] = useState("");
  const [lmtPrice, setlmtPrice] = useState("");
  const [type, setType] = React.useState("Market");
  const [orderPlList, setOrderPlList] = useState([]);
  const addOrder = (newOrder) => {
    setOrderPlList((prevData) => [...prevData, newOrder]);
    console.log(orderPlList);
  };
  const [order, setOrder] = useState(null);
  const [modalShow, setModalShow] = React.useState(false);
  const [radioValue, setRadioValue] = useState("1");
  const [shares, setShares] = useState("");

  const radios = [
    { name: "Market", value: "1" },
    { name: "Limit", value: "2" },
  ];

  const API_KEY2 = "642170e62900b1.66857007";
  let API_Call2 = `https://eodhistoricaldata.com/api/real-time/${shares}.US?fmt=json&api_token=${API_KEY2}`;

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
          <PieChart chartData={chartData} />
        </Modal.Body>
        <Modal.Footer>
          <Button onClick={props.onHide}>Close</Button>
        </Modal.Footer>
      </Modal>
    );
  }
  const changePriceMkt = () => console.log("change price " + shares);
  {
    fetch(API_Call2)
      .then((response) => response.json())

      .then((data2) => {
        setPrice(data2.close);
        // console.log(price);
      });
  }
  const getType = () => {
    console.log(radioValue);
    if (radioValue == "1") {
      getPrice("Limit");
      setType("Limit");
    } else {
      getPrice("Market");
      setIsPriceShown(false);
      setType("Market");
    }
  };
  const [intervalId, setIntervalId] = useState(0); // [variable, function to set variable
  useEffect(() => {
    const id = setInterval(() => fetchData(), 5000);
    setIntervalId(id);
    return () => clearInterval(id);
  }, []);
  const fetchData = () => {
    // function which gets called every n milliseconds
    fetch("http://localhost:1234/ping", {
      mode: "no-cors", // <---- for CORS, do not delete
      // method: "GET"       // for post request
    })
      // .then((response) => response.json())
      // .then((data) => {
      //   console.log(data);
      // })
      .catch((error) => {
        console.log(error);
      });
  };

  const buyShares = () => {
    const amount = document.getElementById("amount").value;
    // setShares(document.getElementById("shares").value);
    //get data from backend
    //example for get request
    //prints out whatever is in the response
    fetch("http://localhost:1234/trade", {
      mode: "no-cors", // <---- for CORS, do not delete
      method: "POST", // for post request

      //set the body of the request to the data we want to send
      //key-value pairs
      body: JSON.stringify({
        side: "buy",
        ordertype: type,
        amount: amount,
        price: price,
        ticker: shares,
        progress: 0,
        completed: false,
      }),
      //set the content type
      headers: {
        "Content-type": "application/json;",
      },
    });

    console.log("Buying " + amount + " shares of " + shares + " at " + price);
    if (lmtPrice != "") {
      handleAddLmtOrder();
    } else {
      handleAddOrder();
    }
  };
  const sellShares = () => {
    amount = document.getElementById("amount").value;
    // setShares(document.getElementById("shares").value);
    console.log("Selling " + amount + " shares of " + shares);

    //post data to backend
    fetch("http://localhost:1234/trade", {
      mode: "no-cors", // <---- for CORS, do not delete
      method: "POST", // for post request

      //set the body of the request to the data we want to send
      //key-value pairs
      body: JSON.stringify({
        side: "sell",
        ordertype: type,
        amount: amount,
        price: price,
        ticker: shares,
        progress: 0,
        completed: false,
      }),
      //set the content type
      headers: {
        "Content-type": "application/json;",
      },
    });
    if (lmtPrice == "") {
      handleAddSellOrder();
    } else {
      handleAddSellLmtOrder();
    }
  };
  const handleAddOrder = () => {
    const amount = document.getElementById("amount").value;
    addOrder({
      ticker: shares,
      type: type,
      side: "Buy",
      price: price,
      amount: amount,
      date: new Date().toLocaleDateString(),
      status: "Not Filled",
    });
    // console.log(shares, type, price, amount, new Date().toISOString());
    // setOrderPlList([...orderPlList, order]);
    setlmtPrice("");
  };
  const handleAddSellOrder = () => {
    const amount = document.getElementById("amount").value;
    // setShares(document.getElementById("shares").value);
    addOrder({
      ticker: shares,
      type: type,
      side: "Sell",
      price: price,
      amount: amount,
      date: new Date().toLocaleDateString(),
      status: "Not Filled",
    });
    // setOrderPlList([...orderPlList, order]);
  };
  const handleAddLmtOrder = () => {
    const amount = document.getElementById("amount").value;
    // setShares(document.getElementById("shares").value);
    addOrder({
      ticker: shares,
      type: type,
      side: "Buy",
      price: lmtPrice,
      amount: amount,
      date: new Date().toLocaleDateString(),
      status: "Not Filled",
    });
    // setOrder(
    //   "  " +
    //     shares +
    //     "     Lmt Buy    " +
    //     lmtPrice +
    //     "    " +
    //     amount +
    //     "        10/04/23    Filled"
    // );
    // setOrderPlList([...orderPlList, order]);
  };
  const handleAddSellLmtOrder = () => {
    const amount = document.getElementById("amount").value;
    // setShares(document.getElementById("shares").value);
    addOrder({
      ticker: shares,
      type: type,
      side: "Sell",
      price: lmtPrice,
      amount: amount,
      date: new Date().toLocaleDateString(),
      status: "Not Filled",
    });
    // setOrder(
    //   "  " +
    //     shares +
    //     "     Lmt Sell    " +
    //     lmtPrice +
    //     "    " +
    //     amount +
    //     "        10/04/23    Filled"
    // );
    // setOrderPlList([...orderPlList, order]);
  };

  // const getInfo = () => {
  //   setShares(document.getElementById("shares").value);
  // };
  const getPrice = (event) => {
    if (event === "Limit") {
      setIsPriceShown((current) => !current);
    }
    setlmtPrice("");
  };
  const [chartData, setChartData] = useState({
    labels: ["Shares Processed", "Shares Left"],
    datasets: [
      {
        data: [20, 80],
        backgroundColor: ["rgba(40,245,40,1)", "rgba(255,0,0,1)"],
        borderColor: "black",
        borderWidth: 2,
      },
    ],
  });
  const [size, setSize] = React.useState("medium");
  const [fillMode, setFillMode] = React.useState("solid");
  const [rounded, setRounded] = React.useState("small");

  const updatePrice = (price) => {
    this.setState({
      price: this.state.price,
    });
  };

  useEffect(() => {
    const element = document.querySelector("#EqList");
    console.log(element);
  }, []);

  return (
    <div className="" style={{ backgroundColor: "black" }}>
      <div className="flex-container">
        <div className="item text-center main-background-box">
          <div>
            <h2 className="text-white text-center">MAKE A TRADE</h2>
            <div>
              <input
                type="text"
                id="amount"
                placeholder="Select quantity ..."
                rounded={rounded}
                style={{
                  width: "300px",
                  height: "27px",
                  fontSize: 15,
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
                  textField={"name"}
                  valueField={"symbol"}
                  size={size}
                  fillMode={fillMode}
                  rounded={rounded}
                  id="shares"
                  placeholder="Select share ..."
                  onChange={(event) => {
                    if (event === null || event.value === null) {
                      console.log("null");
                      setIsShown(false);
                    } else {
                      setShares(event.value.symbol);
                      setIsShown(true);
                      changePriceMkt();
                    }
                  }}
                />

                <MyModal show={modalShow} onHide={() => setModalShow(false)} />
                <div
                  style={{
                    justifyContent: "space-around",
                  }}
                ></div>
                {isPriceShown ? (
                  <input
                    type="text"
                    id="price"
                    placeholder="Select price..."
                    onChange={(e) => setlmtPrice(e.target.value)}
                    style={{
                      width: "300px",
                      height: "27px",
                      fontSize: 15,
                    }}
                  />
                ) : null}
                <br />
                <div className="" style={{}}>
                  <Button
                    className="margin-right-small"
                    style={{
                      backgroundColor: "#B2CEB7",
                      border: "none",
                      color: "black",
                      width: 90,
                      height: 40,
                    }}
                    onClick={() => {
                      buyShares();
                    }}
                  >
                    Buy
                  </Button>
                  <Button
                    style={{
                      backgroundColor: "#ceb2b2",
                      border: "none",
                      color: "black",
                      width: 90,
                      height: 40,
                    }}
                    onClick={() => {
                      sellShares();
                    }}
                  >
                    Sell
                  </Button>
                  <div className="margin-top-small">
                    <ButtonGroup>
                      {radios.map((radio, idx) => (
                        <ToggleButton
                          key={idx}
                          id={`radio-${idx}`}
                          type="radio"
                          variant={
                            idx % 2 ? "outline-success" : "outline-danger"
                          }
                          name="radio"
                          value={radio.value === null ? "" : radio.value}
                          checked={radioValue === radio.value}
                          style={{ width: 100 }}
                          onChange={(e) => {
                            setRadioValue(e.currentTarget.value);
                            getType();
                          }}
                        >
                          {radio.name}
                        </ToggleButton>
                      ))}
                    </ButtonGroup>
                  </div>
                </div>
              </div>
            </div>
          </div>

          {isShown ? (
            <div className="item">
              <div className="">
                <table className="table mt-3" style={{ color: "white" }}>
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
                <Graph ticker={shares} className="" />
              </div>
            </div>
          ) : null}
        </div>
        <div className="item main-background-box">
          <div className="text-white text-center">
            <h2>Your Trades</h2>
            <div className="center-div">
              <table>
                {orderPlList.length !== 0 ? (
                  <>
                    <thead>
                      <tr className="grid-seven-columns grid-item">
                        {Object.keys(orderPlList[0]).map((key) => (
                          <th>{key}</th>
                        ))}
                      </tr>
                    </thead>
                    <tbody>
                      {orderPlList.map((order) => (
                        <tr className="grid-seven-columns grid-item">
                          {Object.values(order).map((value) => (
                            <td>{value}</td>
                          ))}
                        </tr>
                      ))}
                    </tbody>
                  </>
                ) : (
                  console.log("no orders")
                )}
              </table>
            </div>
          </div>
        </div>
      </div>
    </div>
  );
};
