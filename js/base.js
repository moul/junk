function base(n, to, from) {
    return parseInt(n, from || 10).toString(to);
}
