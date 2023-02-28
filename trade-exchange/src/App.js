import React from "react";
// import "./App.css";
import { BrowserRouter as Router, Route, Routes } from "react-router-dom";
import { Home } from "./pages/Home";
import { Trade } from "./pages/Trade";
import { Landing } from "./pages/Landing";




function App() {
  return (
    <Router>
      <Routes>
        <Route exact path="/" element={<Landing />} />
        <Route exact path="/trade" element={<Trade />} />
        <Route exact path="/Home" element={<Home />} />
      </Routes>
    </Router>
  );
}

export default App;