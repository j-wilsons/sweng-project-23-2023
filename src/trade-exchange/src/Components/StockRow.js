import React, { Component } from "react";
import Plot from "react-plotly.js";
import { useEffect, useState } from "react";

class StockRow extends Component {
  constructor(props) {
    super(props);
    this.state = {
      data: {},
      data2: {},
      price: [],
      change: [],
      chartXVals: [],
      chartYVals: [],
    };
  }

  componentDidMount() {
    const pointerToThis = this;
    const API_KEY = "8836a7fc8bmsh1ce2fd16e5ec3dcp1774fajsne4a03e2d8447";
    const API_KEY2 = "642170e62900b1.66857007";
    let API_Call2 = `https://eodhistoricaldata.com/api/real-time/${this.props.ticker}.US?fmt=json&api_token=${API_KEY2}`;

    let API_Call = `https://www.alphavantage.co/query?function=TIME_SERIES_DAILY_ADJUSTED&symbol=${this.props.ticker}&outputsize=fill&apikey=${API_KEY}`;
    let chartXValsFunction = [];
    let chartYValsFunction = [];

    fetch(API_Call)
      .then((response) => response.json())
      .then((data) => {
        for (var key in data["Time Series (Daily)"]) {
          chartXValsFunction.push(key);
          chartYValsFunction.push(data["Time Series (Daily)"][key]["1. open"]);
        }
        // console.log(this.state.chartXVals);
        pointerToThis.setState({
          chartXVals: chartXValsFunction,
          chartYVals: chartYValsFunction,
          data: {
            price: this.state.chartYVals[0],
            date: this.state.chartXVals[0],
            time: "16:44",
          },
        });
      });

    fetch(API_Call2)
      .then((response) => response.json())

      .then((data2) => {
        // console.log(data2);
        this.setState({
          price: data2.close,
          change: data2.change,
        });
      });
  }

  render() {
    return (
      <tr>
        <td>{this.props.ticker}</td>
        <td>{this.state.price}</td>
        <td>{this.state.change}</td>
        <td>{"09/04/23"}</td>
      </tr>
    );
  }
}
export default StockRow;
