FROM gcc:latest

# Install git
RUN apt-get update && apt-get install -y git --no-install-recommends && rm -rf /var/lib/apt/lists/*

# Clone the repository into the directory
RUN cd /home && git clone https://github.com/dr8co/bush.git

# Compile the program
RUN /home/bush/install.sh

# Run the program
WORKDIR /home
CMD ["bush"]
