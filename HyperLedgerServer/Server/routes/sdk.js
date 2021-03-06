'use strict';

const { FileSystemWallet, Gateway } = require('fabric-network');
const path = require('path');

const ccpPath = path.resolve(__dirname, '../','connection.json');

const user = "user1"
async function send(type, func, args, res){
    try {
        const walletPath = path.join(process.cwd(), './', 'wallet');
        const wallet = new FileSystemWallet(walletPath);
        console.log(`Wallet path: ${walletPath}`);

        const userExists = await wallet.exists(user);
        if (!userExists) {
            console.log(`An identity for the user ${user} does not exist in the wallet`);
            console.log('Run the registUser.js application before retrying');
            return;
        }

        const gateway = new Gateway();
        await gateway.connect(ccpPath, { wallet, identity: user, discovery: { enabled: true, asLocalhost: true } });
        const network = await gateway.getNetwork('channelsales1');
        const contract = network.getContract('smartcar-cc');

        if(type){
            let submitResult = await contract.submitTransaction(func, ...args);

            console.log(`Transaction has been submitted Result ${submitResult} `);
            await gateway.disconnect();
            res.send(JSON.parse(submitResult));
        }else{
            const result = await contract.evaluateTransaction(func, ...args);
            console.log(`Transaction has been evaluated, result is: ${result.toString()}`);
            res.send(JSON.parse(result.toString()));
        }
    } catch (error) {
        console.error(`Failed to submit transaction: ${error}`);
        res.send(`Failed to submit transaction: ${error}`);
    }
}

module.exports = {
    send:send
}
