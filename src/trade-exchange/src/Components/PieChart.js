import React from "react";
import { Pie } from "react-chartjs-2";

function PieChart({ chartData }) {
  return (
    <div className="chart-container">
      <Pie
        data={chartData}
        options={{
          plugins: {
            title: {
              display: true,
            //   text: headLine
            }
          }
        }}
        style={{
          height: 100,

        }}
      />
    </div>
  );
}
export default PieChart;