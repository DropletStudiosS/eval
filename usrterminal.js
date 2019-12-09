const mongoose = require('mongoose');

mongoose.Promise = global.Promise;

const db =  mongoose.connect('mongoodb://localhost', {
useMongoClient: true});




