var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    function adopt(value) { return value instanceof P ? value : new P(function (resolve) { resolve(value); }); }
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
function getData(data) {
    return __awaiter(this, void 0, void 0, function* () {
        return fetch("http://127.0.0.1:3000/api", {
            method: "post",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify(data),
        }).then((res) => {
            return res.json();
        });
    });
}
export { getData };
