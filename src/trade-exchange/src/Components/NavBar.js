import Nav from 'react-bootstrap/Nav';
import NavDropdown from 'react-bootstrap/NavDropdown';

import { useAuth0 } from "@auth0/auth0-react";

const NavBar = () => {
  const { user, isAuthenticated, isLoading} = useAuth0();
  const { loginWithRedirect } = useAuth0();
  const { logout } = useAuth0();

  return (
      <Nav className="navBar" fixed="top" bg="dark" variant="dark" expand="lg" id="basic-navbar-nav">
        <Nav.Link href="Home">Home</Nav.Link>
        <Nav.Link href="Trade">Trade</Nav.Link>
        <Nav.Link href="Admin">Admin</Nav.Link>
        {!isAuthenticated && !isLoading &&
          <div>
          <Nav.Link onClick={() => loginWithRedirect()}>Get Started!</Nav.Link>
          </div>
        }
    
        {isAuthenticated && !isLoading &&  
          <div class="logout">
          <NavDropdown title={user.name} id="nav-dropdown" menuVariant='light'>
           <NavDropdown.Item href="Profile">Profile</NavDropdown.Item>
           <NavDropdown.Item onClick={() => logout({ logoutParams: { returnTo: window.location.origin } })}>Log out</NavDropdown.Item>
          </NavDropdown>
          </div>
        }
      
      </Nav>
  );
}

export default NavBar;