const testAddon = require('./examples/build/Release/examples.node');
// const str = testAddon.sayHi();
// console.log(str);

const wrapper = testAddon
const testVal = wrapper.testNum(123)
const testStr = wrapper.testStr()
const testArr = wrapper.testArr([2.4, 3.3, 4.2, 0.8])
console.log(testVal)
console.log(testStr)
console.log(testArr)

wrapper.testSetSimpleCallback(() => {
    console.log("Hello world")
})
wrapper.testRunSimpleCallback()
wrapper.testSetSimpleCallback(() => {
    console.log("Check reusable")
})
wrapper.testRunSimpleCallback()

wrapper.testTimer.call(new Date(), function (clock) {
    const context = this;
    console.log(context, clock);
}, 5)