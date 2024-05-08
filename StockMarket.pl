% Facts
stock(aapl, 150).
stock(goog, 2000).
stock(msft, 300).
stock(amzn, 3500).

% Rules
buy_stock(StockSymbol, Quantity) :-
    stock(StockSymbol, Price),
    Quantity * Price =< 10000,
    price_trend(StockSymbol, 'up'),
    potential_profit(StockSymbol, Quantity, Profit),
    Profit > 0.

sell_stock(StockSymbol, Quantity) :-
    stock(StockSymbol, Price),
    Quantity * Price >= 5000,
    price_trend(StockSymbol, 'down').

price_trend(StockSymbol, 'up') :-
    % Check if the stock price has been consistently increasing.
    stock(StockSymbol, Price1),
    stock(StockSymbol, Price2),
    Price2 > Price1.

price_trend(StockSymbol, 'down') :-
    % Check if the stock price has been consistently decreasing.
    stock(StockSymbol, Price1),
    stock(StockSymbol, Price2),
    Price2 < Price1.

potential_profit(StockSymbol, Quantity, Profit) :-
    stock(StockSymbol, Price),
    future_price(StockSymbol, NewPrice),
    Profit is (NewPrice - Price) * Quantity.

future_price(StockSymbol, NewPrice) :-
    % Predict future price based on market analysis or historical data.
    % For simplicity, we'll just use a random increase for demonstration purposes.
    stock(StockSymbol, Price),
    NewPrice is Price * 1.1. % Increase by 10%

% Queries
% Check if you should buy AAPL stock with $10,000.
% ?- buy_stock(aapl, Quantity).

% Check if you should sell GOOG stock to get $5,000.
% ?- sell_stock(goog, Quantity).