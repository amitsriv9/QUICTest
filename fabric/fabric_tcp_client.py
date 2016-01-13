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
	 run("./u_tcp_client 130.215.70.3 9800 &")
	 run("./u_tcp_client 130.215.70.3 9850 &")
	 run("./u_tcp_client 130.215.70.3 9900 &")
	 run("./u_tcp_client 130.215.70.3 9950 &")
	 run("./u_tcp_client 130.215.70.3 9975 &")
	 run("./u_tcp_client 130.215.70.3 9875 &")
