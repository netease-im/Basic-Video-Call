import React from "react";

import { Divider } from "antd-mobile";
import "./index.css";
interface NavProps {
  logoSrc?: string;
  appName?: string;
  userRole?: string;
}

const Nav: React.FC<NavProps> = ({ logoSrc, appName, userRole }) => {
  return (
    <nav className="nav">
      <div className={"leftSection"}>
        <img src={logoSrc} alt="Logo" className={"yunxinlogo"} />
        {/* <Divider className={'divider'} /> */}
        <Divider direction="vertical" />
        <span className={"appName"}>{appName}</span>
      </div>

      <div className={"rightSection"}>
        <div className={"userInfo"}>
          {userRole && (
            <>
              <span className={"role"}>登录角色: </span>
              <span className={"userRole"}>{userRole}</span>
            </>
          )}
        </div>
      </div>
    </nav>
  );
};

export default Nav;
