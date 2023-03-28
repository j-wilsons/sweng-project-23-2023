import React from "react";
import "../css/Main.css";
import "../css/Text.css";
import NavBar from "../Components/NavBar";
import TradeCard from "../Components/TradeCard";
// import PropTypes from "prop-types";
import { useState } from "react";
import { useEffect } from "react";
import { MultiColumnComboBox } from "@progress/kendo-react-dropdowns";
import { equities } from "../Components/Equities";
import "@progress/kendo-theme-default/dist/all.css";
import Container from "react-bootstrap/Container";
import Row from "react-bootstrap/Row";
import Col from "react-bootstrap/Col";
import Button from "react-bootstrap/esm/Button";
import ApexChart from "../Components/stockChart";
import axios from "axios";
var amount = 0;
var shares = 0;
let myData; // variable to hold response from backend

const buyShares = () => {
  const amount = document.getElementById("amount").value;
  const shares = document.getElementById("shares").value;
  console.log("Buying " + amount + " shares of " + shares);
  fetch("https://api.npms.io/v2/", { mode: "no-cors" }) // this will "open the url" the mode thing is to stop cors errors which is an error do to the browser not allowing you to access the data
    .then((response) => response.json()) // this changes the reponse into useable data
    .then((data) => { // take the data
      myData = data; // put it in myData
      console.log(data); // print it to the console
    });
};
const sellShares = () => {
  amount = document.getElementById("amount").value;
  shares = document.getElementById("shares").value;
  console.log("Selling " + amount + " shares of " + shares);
  const xhr = new XMLHttpRequest();

  xhr.open("POST", "http://localhost:3000/api/sell-shares");

  xhr.setRequestHeader("Content-Type", "application/json");
  const payload = JSON.stringify({
    amount: amount,
    shares: shares,
  });
  console.log("sent");
  xhr.onreadystatechange = function () {
    if (xhr.readyState === XMLHttpRequest.DONE && xhr.status === 200) {
      console.log("Done");
    }
  };
  xhr.send(payload);
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
const IBMnums = [
  33, 55, 66, 11, 22, 33, 23, 44, 66, 77, 88, 44, 55, 66, 33, 44, 55, 66, 7, 77,
];
const nikeNums = [
  11, 22, 55, 11, 22, 66, 99, 44, 55, 66, 88, 33, 44, 55, 33, 22, 55, 66, 77,
  99,
];
const amzNums = [
  22, 44, 55, 66, 11, 22, 55, 88, 77, 66, 44, 33, 44, 55, 99, 77, 88, 99, 11,
  22,
];
const teslaNums = [
  77, 88, 99, 66, 55, 88, 99, 22, 33, 44, 66, 77, 88, 55, 66, 77, 44, 44, 55,
  66,
];
const numLabels = [
  "test",
  "test",
  "test",
  "test",
  "test",
  "test",
  "test",
  "test",
  "test",
  "test",
  "test",
  "test",
  "test",
  "test",
  "test",
  "test",
  "test",
  "test",
  "test",
  "test",
];
var dataNums = nikeNums;

export const Trade = () => {
  const [visibility, setVisibility] = useState(false);

  const popupCloseHandler = (e) => {
    setVisibility(false);
  };
  const [size, setSize] = React.useState("medium");
  const [fillMode, setFillMode] = React.useState("solid");
  const [rounded, setRounded] = React.useState("small");

  useEffect(() => {
    const element = document.querySelector("#EqList");
    console.log(element);
  }, []);

  return (
    <div className="home">
      <NavBar />
      <div className="row2">
        <div>
          <h2>MAKE A TRADE</h2>
          <div>
            <input
              className="center-text"
              type="text"
              id="amount"
              placeholder="Select amount ..."
              rounded={rounded}
              style={{
                width: "293px",
                height: "27px",
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
                size={size}
                fillMode={fillMode}
                rounded={rounded}
                id="shares"
                placeholder="Select share ..."
              />
            </div>

            <br />
            <div className="row2">
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

        <div className="graph">
          <ApexChart
            data={dataNums}
            data2={IBMnums}
            data3={amzNums}
            data4={teslaNums}
            dLabels={numLabels}
          ></ApexChart>
        </div>
        <div className="right-pos">
          <Container fluid>
            <Row>
              <Col className="container-pos">Current equities</Col>
              <Col className="container-pos">No. Shares</Col>
            </Row>
            <Row>
              <Col className="container-pos">shares</Col>
              <Col className="container-pos">amount</Col>
            </Row>
          </Container>
        </div>
      </div>
    </div>
  );
};
