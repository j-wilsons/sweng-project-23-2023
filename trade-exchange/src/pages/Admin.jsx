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

function bruh2() {
  console.log("bruh2");
}


export const Admin = () => {
    const [chartData, setChartData] = useState({
        labels: Data.map((data) => data.user), 
        datasets: [
          {
            label: "Users Gained ",
            data: Data.map((data) => data.totalShares),
            backgroundColor: [
              "rgba(75,192,192,1)",
              "rgba(100,92,12,1)",
              "rgba(100,92,12,0)",
              "rgba(100,92,100,1)",
              "rgba(75,12,192,1)"
            ],
            borderColor: "black",
            borderWidth: 4
          }
        ]
      });
  return (
    <div className="center">
      <h1>Admin</h1>
      <p className="text-center">Transactions</p>
      <select value={""} onChange={bruh2}>
        <option disabled={true} value="">
          Select a user
        </option>
        {Data.map((data) => (
          <option key={data.user}>{data.user}</option>
        ))}
      </select>
      <PieChart chartData={chartData} headLine="Pie" />
    </div>
  );
};
