Sample init scripts and service configuration for phtevencoind
==========================================================

Sample scripts and configuration files for systemd, Upstart and OpenRC
can be found in the contrib/init folder.

    contrib/init/phtevencoind.service:    systemd service unit configuration
    contrib/init/phtevencoind.openrc:     OpenRC compatible SysV style init script
    contrib/init/phtevencoind.openrcconf: OpenRC conf.d file
    contrib/init/phtevencoind.conf:       Upstart service configuration file
    contrib/init/phtevencoind.init:       CentOS compatible SysV style init script

1. Service User
---------------------------------

All three startup configurations assume the existence of a "phtevencoin" user
and group.  They must be created before attempting to use these scripts.

2. Configuration
---------------------------------

At a bare minimum, phtevencoind requires that the rpcpassword setting be set
when running as a daemon.  If the configuration file does not exist or this
setting is not set, phtevencoind will shutdown promptly after startup.

This password does not have to be remembered or typed as it is mostly used
as a fixed token that phtevencoind and client programs read from the configuration
file, however it is recommended that a strong and secure password be used
as this password is security critical to securing the wallet should the
wallet be enabled.

If phtevencoind is run with the "-server" flag (set by default), and no rpcpassword is set, 
it will use a special cookie file for authentication. The cookie is generated with random 
content when the daemon starts, and deleted when it exits. Read access to this file
controls who can access it through RPC. 

By default the cookie is stored in the data directory, but it's location can be overridden 
with the option '-rpccookiefile'.

This allows for running phtevencoind without having to do any manual configuration.

`conf`, `pid`, and `wallet` accept relative paths which are interpreted as 
relative to the data directory. `wallet` *only* supports relative paths.

For an example configuration file that describes the configuration settings, 
see `contrib/debian/examples/phtevencoin.conf`.

3. Paths
---------------------------------

All three configurations assume several paths that might need to be adjusted.

Binary:              `/usr/bin/phtevencoind`  
Configuration file:  `/etc/phtevencoin/phtevencoin.conf`  
Data directory:      `/var/lib/phtevencoind`  
PID file:            `/var/run/phtevencoind/phtevencoind.pid` (OpenRC and Upstart) or `/var/lib/phtevencoind/phtevencoind.pid` (systemd)  
Lock file:           `/var/lock/subsys/phtevencoind` (CentOS)  

The configuration file, PID directory (if applicable) and data directory
should all be owned by the phtevencoin user and group.  It is advised for security
reasons to make the configuration file and data directory only readable by the
phtevencoin user and group.  Access to phtevencoin-cli and other phtevencoind rpc clients
can then be controlled by group membership.

4. Installing Service Configuration
-----------------------------------

4a) systemd

Installing this .service file consists of just copying it to
/usr/lib/systemd/system directory, followed by the command
`systemctl daemon-reload` in order to update running systemd configuration.

To test, run `systemctl start phtevencoind` and to enable for system startup run
`systemctl enable phtevencoind`

4b) OpenRC

Rename phtevencoind.openrc to phtevencoind and drop it in /etc/init.d.  Double
check ownership and permissions and make it executable.  Test it with
`/etc/init.d/phtevencoind start` and configure it to run on startup with
`rc-update add phtevencoind`

4c) Upstart (for Debian/Ubuntu based distributions)

Drop phtevencoind.conf in /etc/init.  Test by running `service phtevencoind start`
it will automatically start on reboot.

NOTE: This script is incompatible with CentOS 5 and Amazon Linux 2014 as they
use old versions of Upstart and do not supply the start-stop-daemon utility.

4d) CentOS

Copy phtevencoind.init to /etc/init.d/phtevencoind. Test by running `service phtevencoind start`.

Using this script, you can adjust the path and flags to the phtevencoind program by 
setting the PHTEVENCOIND and FLAGS environment variables in the file 
/etc/sysconfig/phtevencoind. You can also use the DAEMONOPTS environment variable here.

5. Auto-respawn
-----------------------------------

Auto respawning is currently only configured for Upstart and systemd.
Reasonable defaults have been chosen but YMMV.

