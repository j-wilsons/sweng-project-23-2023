import React from "react";
import "./css/NavBar.css";
import { BrowserRouter as Router, Route, Routes } from "react-router-dom";
import { Home } from "./Pages/Home";
import { Trade } from "./Pages/Trade";
import { Admin } from "./Pages/Admin";


function App() {
  return (
    <Router>
      <Routes>
      <Route index element={<Home />}/>
        <Route exact path="/home" element={<Home />} />
        <Route exact path="/trade" element={<Trade />} />
        <Route exact path="/admin" element={<Admin />} />
      </Routes>
    </Router>
  );
}

export default App;