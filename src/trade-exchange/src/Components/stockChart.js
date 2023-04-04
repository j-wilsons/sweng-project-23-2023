import { Colors } from 'chart.js';
import React from 'react'
import ReactApexChart from 'react-apexcharts';

export const ApexChart = ({data, data2, data3, data4, dLabels}) => {
    
        const options = {
          chart: {
            type: 'area',
            stacked: false,
            height: 350,
            foreColor: 'white',
            zoom: {
              type: 'x',
              enabled: true,
              autoScaleYaxis: true
            },
            toolbar: {
              autoSelected: 'zoom'
            },
           
          },
          dataLabels: {
            enabled: false,
           
           
           
          },
          legend: {
            style: {
                fontSize: '12px',
                colors: ["#FA1109"],
                width: 50
            }
          },
          markers: {
            size: 0,
           
          },
          title: {
            text: 'Stock Price Movement',
            align: 'left',
            style: {
                color: '#fff'
            }
          },
          fill: {
            type: 'gradient',
            gradient: {
              shadeIntensity: 1,
              inverseColors: false,
              opacityFrom: 0.5,
              opacityTo: 0,
              stops: [0, 90, 100]
            },
          },
          
          xaxis: {
            categories: dLabels,
            style: {
                colors: ['#fff']
            }
          },
    
}
const series = [{
    name: 'Nike',
    data: data
  },
{
    name: 'IBM',
    data: data2
},
{
    name: 'Amazon',
    data: data3
},
{
    name: 'Tesla',
    data: data4
}]
    
      return (
  <div id="chart">
<ReactApexChart options={options} series={series} type="area" height={350} />
</div>
      );
    
    
};
export default ApexChart;