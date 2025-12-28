FROM mirror.gcr.io/library/node:18-alpine

WORKDIR /database

# Copy package files
COPY package*.json ./

# Install dependencies
RUN npm install

# Copy migration script and schema
COPY . .

# Run migration
CMD ["node", "migrate.js"]
