from __future__ import with_statement
from fabric.api import local, run, abort, settings, cd
from fabric.contrib.console import confirm


#quic-b2.cs.wpi.edu
def host_type():
    local('uname -s')
    #run('uname -s')


def deploy():
    code_dir= '/home/aksrivastava/networkTest'
    with cd(code_dir):
	 run("./u_tcp_server 9800 2011-Aug02-MPCV-HIB-splash.mp4 &")
	 run("./u_tcp_server 9850 2011-Aug02-MPCV-HIB-splash.mp4 &")
	 run("./u_tcp_server 9900 2011-Aug02-MPCV-HIB-splash.mp4 &")
	 run("./u_tcp_server 9950 2011-Aug02-MPCV-HIB-splash.mp4 &")
	 run("./u_tcp_server 9975 2011-Aug02-MPCV-HIB-splash.mp4 &")
	 run("./u_tcp_server 9875 2011-Aug02-MPCV-HIB-splash.mp4 &")
