import Chart from "chart.js/auto";
import { CategoryScale } from "chart.js";
import { useState } from "react";
import { Data } from "../Components/Data";
// import "./styles.css";

Chart.register(CategoryScale);
 
export const Graph = () => {
  const [chartData, setChartData] = useState({
    labels: Data.map((data) => data.year), 
    datasets: [
      {
        label: "Users Gained ",
        data: Data.map((data) => data.userGain),
        borderColor: "black",
        borderWidth: 2,
        backgroundColor: "rgba(75,192,192,1)"
      }
    ]
  });
 
  return (
    <div className="App">
      <p>Using Chart.js in React</p>
    </div>
  );
}