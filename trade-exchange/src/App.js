import React from "react";
// import "./App.css";
import "./css/NavBar.css";
import { BrowserRouter as Router, Route, Routes } from "react-router-dom";
import { Home } from "./pages/Home";
import { Trade } from "./pages/Trade";

function App() {
  return (
    <Router>
      <Routes>
      <Route index element={<Home />}/>
        <Route exact path="/home" element={<Home />} />
        <Route exact path="/trade" element={<Trade />} />
      </Routes>
    </Router>
  );
}

export default App;