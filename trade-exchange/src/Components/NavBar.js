import Container from 'react-bootstrap/Container';
import Nav from 'react-bootstrap/Nav';
import Navbar from 'react-bootstrap/Navbar';
import NavDropdown from 'react-bootstrap/NavDropdown';


const NavBar = () => {
  return (
    <Navbar fixed="top" bg="dark" variant="dark" expand="lg">
      <Container>
      <Nav className="navBar">
        <Navbar.Brand href="Home">Sweng23</Navbar.Brand>
        <Navbar.Toggle aria-controls="basic-navbar-nav" />
        <Navbar.Collapse id="basic-navbar-nav">
            <div className = "N1">
            <Nav.Link href="Home">Home</Nav.Link>
            </div>
            <div className = "N2">
            <Nav.Link href="Trade">Trade</Nav.Link>
            </div>
            <NavDropdown title="Account" id="basic-nav-dropdown">
              <NavDropdown.Item href="#login">Sign up</NavDropdown.Item>
              <NavDropdown.Item href="#info">
                Login
              </NavDropdown.Item>
              <NavDropdown.Item href="#action/3.3">Info</NavDropdown.Item>
              <NavDropdown.Divider />
              <NavDropdown.Item href="#action/3.4">
                Separated link
              </NavDropdown.Item>
            </NavDropdown>
            <div>
            <Nav.Link href="Admin">Admin</Nav.Link>
            </div>
        </Navbar.Collapse>
        </Nav>
      </Container>
    </Navbar>
  );
}

export default NavBar;