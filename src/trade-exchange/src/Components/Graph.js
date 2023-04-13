import React, { useState, useEffect } from "react";
import Plot from "react-plotly.js";

const Graph = (props) => {
  const [data, setData] = useState({});
  const [data2, setData2] = useState({});
  const [price, setPrice] = useState([]);
  const [change, setChange] = useState([]);
  const [chartXVals, setChartXVals] = useState([]);
  const [chartYVals, setChartYVals] = useState([]);

  useEffect(() => {
    const API_KEY = "8836a7fc8bmsh1ce2fd16e5ec3dcp1774fajsne4a03e2d8447";
    const API_KEY2 = "642170e62900b1.66857007";
    let API_Call2 = `https://eodhistoricaldata.com/api/real-time/${props.ticker}.US?fmt=json&api_token=${API_KEY2}`;

    let API_Call = `https://www.alphavantage.co/query?function=TIME_SERIES_DAILY_ADJUSTED&symbol=${props.ticker}&outputsize=fill&apikey=${API_KEY}`;
    let chartXValsFunction = [];
    let chartYValsFunction = [];

    fetch(API_Call)
      .then((response) => response.json())
      .then((data) => {
        for (var key in data["Time Series (Daily)"]) {
          chartXValsFunction.push(key);
          chartYValsFunction.push(data["Time Series (Daily)"][key]["1. open"]);
        }
        // console.log(chartXVals);
        setChartXVals(chartXValsFunction);
        setChartYVals(chartYValsFunction);
        setData({
          price: chartYValsFunction[0],
          date: chartXValsFunction[0],
          time: "16:44",
        });
      });

    fetch(API_Call2)
      .then((response) => response.json())
      .then((data2) => {
        // console.log(data2);
        setPrice(data2.close);
        setChange(data2.change);
      });
  }, [props.ticker]);

  return (
    <Plot
      className=""
      data={[
        {
          x: chartXVals,
          y: chartYVals,
          type: "scatter",
          mode: "linemarkers",
          marker: { color: "blue" },
        },
      ]}
      layout={{ title: props.ticker }}
      // responsive={true}
      useResizeHandler={true}
      style={{
        color: "white",
      }}
    ></Plot>
  );
};

export default Graph;
