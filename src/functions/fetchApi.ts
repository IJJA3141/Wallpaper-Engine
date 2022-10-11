async function getData() {
  //return await fetch("http://127.0.0.1:3000/api");
  return await fetch("https://api.github.com/users/xiaotian/repos")
}

export { getData };