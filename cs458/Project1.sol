// SPDX-License-Identifier: MIT
pragma solidity ^0.8.10;

//function functionName() public functionType returns (returnType) { BODY }

contract Project1 {

    uint[] public Randoms;
    uint[] public Rands = [4, 200, 7, 6, 8, 0, 1, 113];

    /*constructor() public {

    }*/

    //#2
    function GetItemRandoms(uint index) public view returns (uint) {
        return Randoms[index];
    }

    //#3
    function GetRandoms() public view returns (uint[] memory) {
        return Randoms;
    }

    //#4
    function PushToRandoms(uint numToPush) public {
        Randoms.push(numToPush);
    }

    //#5
    function PopFromRands() public {
        Rands.pop();
    }

    //#6 - Instructions are vague, remove by index? In order to not change the length i just set index to 0
    function RemoveFromRandoms(uint indexToRemove) public {
        Randoms[indexToRemove] = 0;
    }

    //#7
    function GetRandomsLength() public view returns (uint) {
        return Randoms.length;
    }

    //#8 - 5 and 3 meant to be hardcoded?
    function RandsAddMod(uint index) public view returns (uint) {
        uint x = Randoms[index];
        uint y = 5;
        uint z = 3;
        return addmod(x,y,z);
    }

    //#9 - same as 8
    function RandsMulMod(uint index) public view returns (uint) {
        uint x = Randoms[index];
        uint y = 5;
        uint z = 3;
        return mulmod(x,y,z);
    }
}