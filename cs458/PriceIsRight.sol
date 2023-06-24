// SPDX-License-Identifier: UNLICENSED
pragma solidity 0.8.17;

contract PriceIsRight {
    struct Bet {
        address betCreator;
        bytes32 commitPrice;
        uint256 prizePool;
        uint256 betAmount;
        uint256 deadline;
        uint256 price;
        bool revealed;
    }

    struct Commitment {
        address bettor;
        bytes32 commit;
        uint256 guess;
    }

    // TODO: create a mapping that maps a uint256 to a Bet struct
    // we will use this to store the bets that users create
    // add this public mapping here and call it 'bets'
    mapping(uint256 => Bet) public bets;

    mapping(uint256 => mapping(address => Commitment)) public guesses;
    mapping(uint256 => mapping(address => bool)) public didGuess;
    mapping(uint256 => address[]) public addressesThatGuessed;
    mapping(uint256 => uint256) public revealCount;
    uint256 public idCounter;


    // Custom errors
    error OwnerCannotGuess();
    error AlreadyGuessed();
    error DeadlinePassed();
    error DeadlineNotPassed();
    error CommitDoesNotMatchRevealed();
    error NotAllRevealed();
    error PriceNotRevealed();
    error NotEnoughValue();

    // Create a new price is right bet
    function createBet(bytes32 _commitPrice, uint256 _deadline) public payable returns (uint256) {
        bets[++idCounter] = Bet(msg.sender, _commitPrice, msg.value, msg.value, _deadline, 0, false);
        return idCounter;
    }

    // Guess a value for a specific bet
    function guessNumber(uint256 _betId, bytes32 _hashedGuess) public payable {
        if (msg.sender == bets[_betId].betCreator) revert OwnerCannotGuess();
        if (didGuess[_betId][msg.sender]) revert AlreadyGuessed();
        if (bets[_betId].deadline < block.timestamp) revert DeadlinePassed();
        if (msg.value != bets[_betId].betAmount) revert NotEnoughValue();

        // TODO: create a Commitment struct with the correct info and assign it to the guesses mapping
        // use the betId that is passed in as a parameter and the address of the person/contract that sent the transaction
        guesses[_betId][msg.sender] = Commitment(msg.sender, _hashedGuess, 0); 
        //no input for guess? cant seem to find anything to put in and another test passes after this.

        didGuess[_betId][msg.sender] = true;
        addressesThatGuessed[_betId].push(msg.sender);
        bets[_betId].prizePool += msg.value;
    }

    // Reveal guess by setting the Commitment.guess field to the value from the commitment
    function revealGuess(uint256 _betId, uint256 _guess, uint256 _salt) public {
        if (bets[_betId].deadline > block.timestamp) revert DeadlineNotPassed();
        if (keccak256(abi.encode(msg.sender, _guess, _salt)) != guesses[_betId][msg.sender].commit) revert CommitDoesNotMatchRevealed();

        guesses[_betId][msg.sender].guess = _guess;
        // TODO: increment the reveal count for the given bet ID by 1
        revealCount[_betId]++;
    }

    // Reveal the correct price for the bet
    function revealBet(uint256 _betId, uint256 _price, uint256 _salt) public {
        if (bets[_betId].deadline > block.timestamp) revert DeadlineNotPassed();
        if (revealCount[_betId] != addressesThatGuessed[_betId].length) revert NotAllRevealed();
        /*TODO: complete this check to make sure the commit matches the revealed BELOW THIS COMMENT*/
        if (bets[_betId].commitPrice != keccak256(abi.encode(msg.sender, _price, _salt))) revert CommitDoesNotMatchRevealed();

        bets[_betId].price = _price;
        bets[_betId].revealed = true;
    }

    // Loops through the guesses of the betId given and finds the bet with the highest guess that is less than or equal to the price.
    function detemineWinner(uint256 _betId) public {
        if (bets[_betId].deadline > block.timestamp) revert DeadlineNotPassed();
        if (!bets[_betId].revealed) revert PriceNotRevealed();

        uint256 price = bets[_betId].price;
        uint256 numberOfGuesses = addressesThatGuessed[_betId].length;
        uint256 bestGuess;
        address winner;

        for (uint256 i = 0; i < numberOfGuesses; ++i) {
            Commitment memory commit = guesses[_betId][addressesThatGuessed[_betId][i]];
            if (commit.guess > bestGuess && commit.guess <= price) {
                bestGuess = commit.guess;
                winner = commit.bettor;
            }
        }

        // This transfers the prizePool to the winner
        if (winner != address(0)) {
            (bool success, ) = payable(winner).call{value: bets[_betId].prizePool}("");
            require(success, "ETH transfer failed");
        } else {
            // If there is not winner, transfer to the creator. Extra credit (10 points): Explain a vulnerability/flaw in this contract. 
            // Answer the EC in the text field on Canvas.
            // TODO: transfer the prizePool value to the betCeator and ensure the transfer succeeds
            (bool success, ) = payable(bets[_betId].betCreator).call{value: bets[_betId].prizePool}("");
            require(success, "ETH transfer failed");
        }
    }

    // Ideally, this would take place completely off chain. Whichever node you run this call on will know your price. 
    function makeCommitment(uint256 _price, uint256 _salt) public view returns (bytes32) {
        return keccak256(abi.encode(msg.sender, _price, _salt));
    }

    // Helper function to find the time a given number of days ahead to use when creating a bet deadline.
    function getDeadlineInDays(uint256 _days) public view returns (uint256) {
        return block.timestamp + (_days * 1 days);
    }
}