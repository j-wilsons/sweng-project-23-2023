import React from "react";
import * as ReactDOM from "react-dom";
import "./css/NavBar.css";
import { BrowserRouter as Router, Route, Routes } from "react-router-dom";
import { Home } from "./pages/Home";
import { Trade } from "./pages/Trade";
import { Admin } from "./pages/Admin";


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