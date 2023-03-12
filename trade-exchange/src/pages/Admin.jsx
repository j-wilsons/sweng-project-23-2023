import "../App.css";
import Chart from "chart.js/auto";
import { CategoryScale } from "chart.js";
import { useState } from "react";
import { Data } from "../Components/Data";
import PieChart from "../Components/PieChart";

Chart.register(CategoryScale);

// const users = [
//     {user: "all", orderCompleted: 0, totalShares: 300, sharesLeft: 150},
//     {user: "steve", orderCompleted: 0, totalShares: 50, sharesLeft: 50},
//     {user: "joe", orderCompleted: 0, totalShares: 100, sharesLeft: 100},
//     {user: "bob", orderCompleted: 1, totalShares: 150, sharesLeft: 0}
// ];
// const users = [
//   { value: "value-1", text: "text-1" },
//   { value: "value-2", text: "text-2" },
//   { value: "value-3", text: "text-3" },
// ];

var user = 0;
function bruh2() {
  console.log("bruh2");
  
    user = document.getElementById("someid").value;
    console.log(user);
}

export const Admin = () => {
  const [chartData, setChartData] = useState({
    labels: ["Shares Processed", "Shares Left"],
    // labels: Data.map((data) => data.user),
    datasets: [
      {
        data: [
          Data[user].totalShares - Data[user].sharesLeft,
          Data[user].sharesLeft,
        ],
        // labels: ["Total Shares", "Shares Left"],
        backgroundColor: ["rgba(40,245,40,1)", "rgba(255,0,0,1)"],
        borderColor: "black",
        borderWidth: 4,
      },
    ],
  });
  return (
    <div className="center">
      <h1 className="text-center">Admin</h1>
      <p className="text-center">Transactions</p>
      {console.log(user)}
      <select
        className="center-horizontal"
        id={"someid"}
        value={"all"}
        onChange={bruh2}
      >
        {/* <option disabled={true} value="">
          Select a user
        </option> */}
        {Data.map((data, index) => (
          <option key={data.user}>{data.user}</option>
        ))}
      </select>
      {console.log(user)}
      <PieChart chartData={chartData} />
    </div>
  );
};
