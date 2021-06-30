'use strict';

const { FileSystemWallet, Gateway, X509WalletMixin } = require('fabric-network');
const path = require('path');

const ccpPath = path.resolve(__dirname, '..', 'connection.json');

async function regi(res,user) {
    try {

        const walletPath = path.join(process.cwd(), '..', 'wallet');
        const wallet = new FileSystemWallet(walletPath);
        console.log(`Wallet path: ${walletPath}`);

        const userExists = await wallet.exists(user);
        if (userExists) {
            console.log(`An identity for the user ${user} already exists in the wallet`);
            return;
        }

        const adminExists = await wallet.exists('admin');
        if (!adminExists) {
            console.log('An identity for the admin user "admin" does not exist in the wallet');
            console.log('Run the enrollAdmin.js application before retrying');
            return;
        }

        const gateway = new Gateway();
        await gateway.connect(ccpPath, { wallet, identity: 'admin', discovery: { enabled: true, asLocalhost: true } });

        const ca = gateway.getClient().getCertificateAuthority();
        const adminIdentity = gateway.getCurrentIdentity();

        const secret = await ca.register({ affiliation: 'org1.department1', enrollmentID: user, role: 'client' }, adminIdentity);
        const enrollment = await ca.enroll({ enrollmentID: user1, enrollmentSecret: secret });
        const userIdentity = X509WalletMixin.createIdentity('Sales1Org', enrollment.certificate, enrollment.key.toBytes());
        await wallet.import(user, userIdentity);
        console.log(`Successfully registered and enrolled admin user ${user} and imported it into the wallet`);
        res.send('success')

    } catch (error) {
        console.error(`Failed to register user ${user1}: ${error}`);
        process.exit(1);
    }
}

// regi(res,user);


module.exports = regi