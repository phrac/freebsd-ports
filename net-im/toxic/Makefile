# Created by: Derek Musselmann aka phrac <derek@disflux.com>
# $FreeBSD$

PORTNAME=	toxic
PORTVERSION=	20140302
CATEGORIES=	net-im
MASTER_SITES=	GH

MAINTAINER=	derek@disflux.com
COMMENT=	The reference command line interface for Tox

LICENSE=	GPLv3

LIB_DEPENDS=	libtoxcore.so:${PORTSDIR}/net-im/tox-core

USE_GITHUB=	yes
GH_ACCOUNT=	Tox
GH_PROJECT=	toxic
GH_COMMIT=	7f38c3c
GH_TAGNAME=	${GH_COMMIT}

USE_AUTOTOOLS=	autoconf

pre-configure:
	@cd ${WRKSRC} && ${AUTORECONF} -i

.include <bsd.port.mk>
