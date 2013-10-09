# -*- mode: ruby -*-
# vi: set ft=ruby :
# Inspired by: https://github.com/creack/dotfiles/blob/master/Vagrantfile

GIT_USERNAME = ENV['GIT_USERNAME']
GIT_EMAIL = ENV['GIT_EMAIL']


Vagrant::Config.run do |config|
  config.vm.define :junk, primary: true do |junk|
    junk.vm.box = 'junk'
    junk.vm.box_url = 'http://cloud-images.ubuntu.com/vagrant/raring/current/raring-server-cloudimg-amd64-vagrant-disk1.box'

    junk.vm.forward_port 8080, 4567
  end

  config.vm.define :coreos do |coreos|
    coreos.vm.box = 'coreos'
    coreos.vm.box_url = 'http://storage.core-os.net/coreos/amd64-generic/dev-channel/coreos_production_vagrant.box'
  end

  config.vm.define :docker_dev do |docker_dev|
    docker_dev.vm.box = 'docker'
    docker_dev.vm.box_url = 'http://cloud-images.ubuntu.com/vagrant/raring/current/raring-server-cloudimg-amd64-vagrant-disk1.box'

    ### Running first time
    pkg_cmd = "[ -f /usr/bin/git ] || ("

    # Install basic env, git/mercurial, docker dependencies, emacs, zsh, etc
    pkg_cmd << "apt-get update -qq; export DEBIAN_FRONTEND=noninteractive; apt-get install -q -y linux-image-extra-3.8.0-19-generic build-essential mercurial git lxc aufs-tools bsdtar htop most emacs24 zsh tmux ngrep tcpdump unzip ntp; "

    # Change default shell
    pkg_cmd << "chsh -s /bin/bash vagrant; "

    # Create docker group and add vagrant user to it
    pkg_cmd << "groupadd docker; "
    pkg_cmd << "usermod -a -G docker vagrant; "

    # Retrieve the dotfiles config
    pkg_cmd << "HOME=/home/vagrant make; "
    pkg_cmd << "[[ -n $GIT_USERNAME ]] && git config --global user.name $GIT_USERNAME; "
    pkg_cmd << "[[ -n $GIT_EMAIL ]] && git config --global user.email $GIT_EMAIL; "

    # Checkout golang source and install them
    pkg_cmd << "echo 'Cloning Go repository'; hg clone http://code.google.com/p/go /home/vagrant/goroot; "
    pkg_cmd << "cd /home/vagrant/goroot/src; ./all.bash; "

    # Make sure the GOPATH and GOROOT are correctly set
    pkg_cmd << "echo 'export GOPATH=~/go' >> /home/vagrant/.zshrc; export GOPATH=/home/vagrant/go; "
    pkg_cmd << "echo 'export GOROOT=~/goroot' >> /home/vagrant/.zshrc; export GOROOT=/home/vagrant/goroot; "
    pkg_cmd << "echo 'export GOBIN=$GOROOT/bin' >> /home/vagrant/.zshrc; export GOBIN=$GOROOT/bin; "
    pkg_cmd << "echo 'export PATH=$GOBIN:$PATH' >> /home/vagrant/.zshrc; export PATH=$GOBIN:$PATH; "

    # Install godef for symbol/tags lookup
    pkg_cmd << "go get code.google.com/p/rog-go/exp/cmd/godef; "
    # Install gocode completion
    pkg_cmd << "go get github.com/nsf/gocode; "
    # Install goflymake
    pkg_cmd << "go get github.com/dougm/goflymake; "
    # Install gocov
    pkg_cmd << "go get github.com/axw/gocov/gocov; "

    # Checkout docker sources
    pkg_cmd << "go get github.com/dotcloud/docker; ln -s /home/vagrant/go/src/github.com/dotcloud/docker /home/vagrant/docker; "
    pkg_cmd << "cd /home/vagrant/docker; git checkout master; "

    # Make sure we have the correct permissions
    pkg_cmd << "chown -R vagrant:vagrant /home/vagrant; "

    pkg_cmd << "); "

    docker_dev.vm.provision :shell, :inline => pkg_cmd
  end

  config.vm.define :docker do |docker|
    # Setup virtual machine box. This VM configuration code is always executed.
    docker.vm.box = ENV['BOX_NAME'] || "ubuntu"
    docker.vm.box_url = ENV['BOX_URI'] || "http://files.vagrantup.com/precise64.box"

    docker.ssh.forward_agent = true

    # Provision docker and new kernel if deployment was not done.
    # It is assumed Vagrant can successfully launch the provider instance.
    if Dir.glob("#{File.dirname(__FILE__)}/.vagrant/machines/default/*/id").empty?
      # Add lxc-docker package
      pkg_cmd = "wget -q -O - https://get.docker.io/gpg | apt-key add -;" \
        "echo deb http://get.docker.io/ubuntu docker main > /etc/apt/sources.list.d/docker.list;" \
        "apt-get update -qq; apt-get install -q -y --force-yes lxc-docker; "
      # Add Ubuntu raring backported kernel
      pkg_cmd << "apt-get update -qq; apt-get install -q -y linux-image-generic-lts-raring; "
      # Add guest additions if local vbox VM. As virtualbox is the default provider,
      # it is assumed it won't be explicitly stated.
      if ENV["VAGRANT_DEFAULT_PROVIDER"].nil? && ARGV.none? { |arg| arg.downcase.start_with?("--provider") }
        pkg_cmd << "apt-get install -q -y linux-headers-generic-lts-raring dkms; " \
          "echo 'Downloading VBox Guest Additions...'; " \
          "wget -q http://dlc.sun.com.edgesuite.net/virtualbox/4.2.12/VBoxGuestAdditions_4.2.12.iso; "
        # Prepare the VM to add guest additions after reboot
        pkg_cmd << "echo -e 'mount -o loop,ro /home/vagrant/VBoxGuestAdditions_4.2.12.iso /mnt\n" \
          "echo yes | /mnt/VBoxLinuxAdditions.run\numount /mnt\n" \
            "rm /root/guest_additions.sh; ' > /root/guest_additions.sh; " \
          "chmod 700 /root/guest_additions.sh; " \
          "sed -i -E 's#^exit 0#[ -x /root/guest_additions.sh ] \\&\\& /root/guest_additions.sh#' /etc/rc.local; " \
          "echo 'Installation of VBox Guest Additions is proceeding in the background.'; " \
          "echo '\"vagrant reload\" can be used in about 2 minutes to activate the new guest additions.'; "
      end
      # Activate new kernel
      pkg_cmd << "shutdown -r +1; "
      docker.vm.provision :shell, :inline => pkg_cmd
    end

    (49000..49900).each do |port|
      docker.vm.forward_port port, port
      #docker.vm.network :forwarded_port, :host => port, :guest => port
    end

  end

end
