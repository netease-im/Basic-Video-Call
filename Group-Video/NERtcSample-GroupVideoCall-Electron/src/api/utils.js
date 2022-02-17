
var randUid = (len)=>{
    if (typeof(len) === "undefined" || len == null || typeof(len) !== "number"){
        len = 6;
    }
    let code = '';
    let codeLength = len;
    let random = new Array(0, 1, 2, 3, 4, 5, 6, 7, 8, 9);
    for (var i = 0; i < codeLength; i++) {
        let index = Math.floor(Math.random() * 9);
        code += random[index];
    }
   return code;
}

export default {
    randUid,
}
