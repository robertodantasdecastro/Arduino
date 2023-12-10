-- phpMyAdmin SQL Dump
-- version 3.4.11.1deb2
-- http://www.phpmyadmin.net
--
-- Máquina: localhost
-- Data de Criação: 03-Jun-2014 às 21:54
-- Versão do servidor: 5.5.37
-- versão do PHP: 5.4.4-14+deb7u9

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Base de Dados: `irrigauto`
--

-- --------------------------------------------------------

--
-- Estrutura da tabela `bombas`
--

CREATE TABLE IF NOT EXISTS `bombas` (
  `id` int(4) NOT NULL AUTO_INCREMENT,
  `id_modulo` int(4) NOT NULL,
  `nome` varchar(50) NOT NULL,
  `descricao` varchar(250) DEFAULT NULL,
  `potencia` varchar(50) DEFAULT NULL,
  `lat` varchar(15) DEFAULT NULL,
  `lon` varchar(15) DEFAULT NULL,
  `tipo` varchar(10) DEFAULT NULL,
  `ativo` int(1) NOT NULL,
  `ci` varchar(1) NOT NULL,
  `porta` varchar(4) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=5 ;

--
-- Extraindo dados da tabela `bombas`
--

INSERT INTO `bombas` (`id`, `id_modulo`, `nome`, `descricao`, `potencia`, `lat`, `lon`, `tipo`, `ativo`, `ci`, `porta`) VALUES
(1, 1, 'BOMBA 1', NULL, NULL, NULL, NULL, 'LIGA', 1, 'A', '13'),
(2, 1, 'BOMBA 2', NULL, NULL, NULL, NULL, 'LIGA', 1, 'A', '14'),
(3, 1, 'BOMBA 3', NULL, NULL, NULL, NULL, 'LIGA', 1, 'A', '15'),
(4, 1, 'BOMBA 4', NULL, NULL, NULL, NULL, 'LIGA', 0, 'A', '16');

-- --------------------------------------------------------

--
-- Estrutura da tabela `botoes`
--

CREATE TABLE IF NOT EXISTS `botoes` (
  `id` int(4) NOT NULL AUTO_INCREMENT,
  `id_menu` int(4) NOT NULL,
  `id_painel` int(4) NOT NULL,
  `id_modulo` int(4) NOT NULL,
  `nome` varchar(50) NOT NULL,
  `descricao` varchar(50) NOT NULL,
  `class1` varchar(50) NOT NULL,
  `class_Ico` varchar(50) NOT NULL,
  `href` varchar(50) NOT NULL,
  `ativo` int(2) DEFAULT NULL,
  `acesso` int(2) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=11 ;

--
-- Extraindo dados da tabela `botoes`
--

INSERT INTO `botoes` (`id`, `id_menu`, `id_painel`, `id_modulo`, `nome`, `descricao`, `class1`, `class_Ico`, `href`, `ativo`, `acesso`) VALUES
(1, 2, 1, 1, 'Páginas', 'Configurar Páginas do sistema', 'btn btn-primary', 'fa fa-desktop', 'config/paginas.php', 0, 1),
(2, 2, 1, 1, 'Usrs.', 'Configurar Usuários do sistema', 'btn btn-primary', 'fa fa-group', 'config/usuarios.php', 1, 1),
(3, 2, 1, 1, 'Tempo', 'Configurar Data e Tempo do sistema', 'btn btn-primary', 'fa fa-clock-o', 'config/tempo.php', 1, 1),
(4, 2, 1, 1, 'Áreas', 'Configurar as áreas de irrgação do sistema', 'btn btn-primary', 'fa fa-sitemap', 'config/areas.php', 1, 1),
(5, 2, 1, 1, 'Sensor.', 'Configurar os sensores das areas de irrigaçao', 'btn btn-primary', 'fa fa-dashboard', 'config/sensores.php', 0, 1),
(6, 2, 2, 1, 'Modo', 'Modo de operação do sistema - Manual / Auto', 'btn btn-primary', 'fa fa-magic', 'config/modo.php', 0, 1),
(7, 2, 2, 1, 'Agenda', 'Agenda de irrigação do mudo manual.', 'btn btn-primary', 'fa fa-calendar', 'config/agenda.php', 1, 1),
(8, 2, 2, 1, 'Culturas', 'Configura as culturas para o modo auto-sensores.', 'btn btn-primary', 'fa fa-leaf', 'config/culturas.php', 1, 1),
(9, 2, 2, 1, 'Plantil', 'Relacinar as culturas as areas de pantil', 'btn btn-primary', 'fa fa-pagelines', 'config/plantil.php', 0, 1),
(10, 2, 2, 1, 'Ciclos', 'Configura os ciclos de plantil', 'btn btn-primary', 'fa fa-refresh', 'config/plantil.php', 1, 1);

-- --------------------------------------------------------

--
-- Estrutura da tabela `configuracao`
--

CREATE TABLE IF NOT EXISTS `configuracao` (
  `id` int(4) NOT NULL AUTO_INCREMENT,
  `id_modulo` int(4) NOT NULL,
  `fuso_horario` float NOT NULL,
  `delay_verifica` int(4) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=2 ;

--
-- Extraindo dados da tabela `configuracao`
--

INSERT INTO `configuracao` (`id`, `id_modulo`, `fuso_horario`, `delay_verifica`) VALUES
(1, 1, -3, 1);

-- --------------------------------------------------------

--
-- Estrutura da tabela `eventos`
--

CREATE TABLE IF NOT EXISTS `eventos` (
  `id` int(4) NOT NULL AUTO_INCREMENT,
  `id_valvula` int(4) NOT NULL,
  `id_usuario` int(4) NOT NULL,
  `data_hora_atual` datetime NOT NULL,
  `data_hora_anterior` datetime DEFAULT NULL,
  `estado_atual` varchar(2) NOT NULL,
  `estado_anterior` varchar(2) DEFAULT NULL,
  `comando_atual` varchar(20) DEFAULT NULL,
  `comando_anterior` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Estrutura da tabela `menu`
--

CREATE TABLE IF NOT EXISTS `menu` (
  `id` int(4) NOT NULL AUTO_INCREMENT,
  `nome` varchar(50) NOT NULL,
  `descricao` varchar(150) DEFAULT NULL,
  `id_modulo` int(4) DEFAULT NULL,
  `publico` tinyint(1) NOT NULL,
  `classPrimaria` varchar(50) NOT NULL,
  `classIcone` varchar(50) NOT NULL,
  `href` varchar(100) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=5 ;

--
-- Extraindo dados da tabela `menu`
--

INSERT INTO `menu` (`id`, `nome`, `descricao`, `id_modulo`, `publico`, `classPrimaria`, `classIcone`, `href`) VALUES
(1, 'Início', 'Tela inicial do sistema.', 1, 1, 'btn btn-default', 'fa fa-home fa-lg fa-1x sombraTexto', 'index.php'),
(2, 'Configurar', 'Configurar ciclos do sistema de irrigação.', 1, 0, 'btn btn-primary', 'fa fa-cogs fa-lg fa-1x sombraTexto', 'configurar.php'),
(3, 'Monitorar', 'Seu sistema em tempo real!', 1, 1, 'btn btn-warning', 'fa fa-eye fa-lg fa-1x sombraTexto', 'monitorar.php'),
(4, 'Estatisticas', 'Estatísticas de uso do seu sistema!', 1, 1, 'btn btn-info', 'fa fa-bar-chart-o fa-lg fa-1x sombraTexto', 'estatisticas.php');

-- --------------------------------------------------------

--
-- Estrutura da tabela `modulo`
--

CREATE TABLE IF NOT EXISTS `modulo` (
  `id` int(4) NOT NULL AUTO_INCREMENT,
  `id_usuario` int(4) NOT NULL,
  `modelo` varchar(25) NOT NULL,
  `versao` varchar(25) NOT NULL,
  `estado` tinyint(1) NOT NULL,
  `nome` varchar(100) NOT NULL,
  `descricao` varchar(300) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=3 ;

--
-- Extraindo dados da tabela `modulo`
--

INSERT INTO `modulo` (`id`, `id_usuario`, `modelo`, `versao`, `estado`, `nome`, `descricao`) VALUES
(1, 1, 'irrig@uto server 1.0', '1.0', 1, 'IrrigautoCORE - Modúlo de controle de irrigação', 'Sistema de Controle de irrigaçao controlador por computador\r\nV. 1.0a'),
(2, 1, 'IrrigautoCORE2', '1.0', 1, 'IrrigautoCORE - Módulo de controle de sistema de irrigação automatizado.', 'Sistema de controle V 1.0a');

-- --------------------------------------------------------

--
-- Estrutura da tabela `TitulosPainel`
--

CREATE TABLE IF NOT EXISTS `TitulosPainel` (
  `id` int(4) NOT NULL AUTO_INCREMENT,
  `id_menu` int(4) NOT NULL,
  `id_mudulo` int(4) NOT NULL,
  `nome` varchar(50) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=3 ;

--
-- Extraindo dados da tabela `TitulosPainel`
--

INSERT INTO `TitulosPainel` (`id`, `id_menu`, `id_mudulo`, `nome`) VALUES
(1, 2, 1, 'Sistema'),
(2, 2, 1, 'Programas');

-- --------------------------------------------------------

--
-- Estrutura da tabela `usuarios`
--

CREATE TABLE IF NOT EXISTS `usuarios` (
  `id` int(4) NOT NULL AUTO_INCREMENT,
  `nome` varchar(250) NOT NULL,
  `usuario` varchar(20) NOT NULL,
  `email` varchar(300) NOT NULL,
  `Telefone` varchar(20) DEFAULT NULL,
  `senha` varchar(100) NOT NULL,
  `acesso` int(2) NOT NULL,
  `ativo` tinyint(1) NOT NULL,
  `id_modulo` int(4) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=5 ;

--
-- Extraindo dados da tabela `usuarios`
--

INSERT INTO `usuarios` (`id`, `nome`, `usuario`, `email`, `Telefone`, `senha`, `acesso`, `ativo`, `id_modulo`) VALUES
(1, 'Roberto Dantas de Castro', 'roberto', 'roberto@dantasdecastro.com.br', NULL, 'e959088c6049f1104c84c9bde5560a13', 2, 1, 1),
(2, 'Julho Neto', 'julhoneto', 'julho@teste.com', NULL, '698dc19d489c4e4db73e28a713eab07b', 1, 1, 1),
(3, 'Alice Augusta', 'alice', 'alice@augusta.com', NULL, '698dc19d489c4e4db73e28a713eab07b', 1, 1, 1),
(4, 'Antonio Heitor', 'aheitor', 'antonioheitor4@gmail.com', NULL, 'aheitor', 1, 1, 1);

-- --------------------------------------------------------

--
-- Estrutura da tabela `valvulas`
--

CREATE TABLE IF NOT EXISTS `valvulas` (
  `id` int(4) NOT NULL AUTO_INCREMENT,
  `id_bomba` int(4) NOT NULL,
  `nome` varchar(30) NOT NULL,
  `descricao` varchar(100) DEFAULT NULL,
  `lat` varchar(15) DEFAULT NULL,
  `lon` varchar(15) DEFAULT NULL,
  `atividade` int(1) DEFAULT NULL,
  `ativo` int(1) NOT NULL,
  `ci` varchar(1) NOT NULL,
  `porta` varchar(4) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=13 ;

--
-- Extraindo dados da tabela `valvulas`
--

INSERT INTO `valvulas` (`id`, `id_bomba`, `nome`, `descricao`, `lat`, `lon`, `atividade`, `ativo`, `ci`, `porta`) VALUES
(1, 1, 'V1', NULL, NULL, NULL, NULL, 1, 'A', '0'),
(2, 1, 'V2', NULL, NULL, NULL, NULL, 1, 'A', '1'),
(3, 1, 'V3', NULL, NULL, NULL, NULL, 1, 'A', '2'),
(4, 1, 'V4', NULL, NULL, NULL, NULL, 1, 'A', '3'),
(5, 2, 'V1', NULL, NULL, NULL, NULL, 1, 'A', '4'),
(6, 2, 'V2', NULL, NULL, NULL, NULL, 1, 'A', '5'),
(7, 2, 'V3', NULL, NULL, NULL, NULL, 1, 'A', '6'),
(8, 2, 'V4', NULL, NULL, NULL, NULL, 1, 'A', '7'),
(9, 3, 'V1', NULL, NULL, NULL, NULL, 1, 'A', '8'),
(10, 3, 'V2', NULL, NULL, NULL, NULL, 1, 'A', '9'),
(11, 3, 'V3', NULL, NULL, NULL, NULL, 1, 'A', '10'),
(12, 3, 'V4', NULL, NULL, NULL, NULL, 1, 'A', '11');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
