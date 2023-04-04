

import { useAuth0 } from "@auth0/auth0-react";

const Username = () => {
  const { user, isAuthenticated } = useAuth0();

  if (isAuthenticated) {
  return user.nickname
  }

  else {
    return "Account"
  }
}

export default Username;

