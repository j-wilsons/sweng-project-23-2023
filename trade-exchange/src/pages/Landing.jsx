import "../css/Main.css";
import "../css/Text.css";
import "../components/login.js";
import "../components/logout.js";
import "../components/profile.js";

import { useAuth0 } from "@auth0/auth0-react";
import { Button } from "react-bootstrap";
import LoginButton from "../components/login.js";
import LogoutButton from "../components/logout.js";

export const Landing = () => {
    const { user, isAuthenticated, isLoading } = useAuth0();
    const { loginWithRedirect } = useAuth0();

    if (isLoading) {
        return <div>Loading ...</div>;
    }


    return (
        <div className="App">
        <div className="left">
            <h1 className="title">Trade Exchange</h1>
            <p className="subtitle">
            A trading platform for the modern age.
            </p>
        </div>
        <div className="right">
            <Button
            className="GetStartedButton"
            onClick={() => loginWithRedirect()}
            variant="primary"
            >
            Get Started!
            </Button>
            <LoginButton/>
            <LogoutButton/>
            {isAuthenticated && (
                <div>
                <img src={user.picture} alt={user.name} />
                <h2>{user.html_url}</h2>
                <p>{user.email}</p>
                </div>
            )}
        </div>
        </div>
    );


    
};  
   




