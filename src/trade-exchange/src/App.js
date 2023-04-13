import React from "react";
import * as ReactDOM from "react-dom";
import "./css/NavBar.css";
import "./App.css";
import NavBar from "./Components/NavBar";
import { BrowserRouter as Router, Route, Routes } from "react-router-dom";
import { Home } from "./pages/Home";
import { Trade } from "./pages/Trade";
import { Admin } from "./pages/Admin";


function App() {
  return (
    <Router className="background-black">
      <NavBar />
      <Routes>
        <Route index element={<Home />} />
        <Route exact path="/home" element={<Home />} />
        <Route exact path="/trade" element={<Trade />} />
      </Routes>
    </Router>
  );
}

export default App;
